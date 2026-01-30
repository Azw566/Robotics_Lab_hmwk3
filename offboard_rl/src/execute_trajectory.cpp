#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <cmath>
#include <vector>
#include <px4_msgs/msg/vehicle_local_position.hpp>
#include <px4_msgs/msg/vehicle_attitude.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <offboard_rl/utils.h>
#include <unsupported/Eigen/Splines>

using namespace std::chrono_literals;
using namespace px4_msgs::msg;

class ExecuteTrajectory : public rclcpp::Node
{
public:
    ExecuteTrajectory() : Node("execute_trajectory")
    {
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        // Subscribers
        local_position_subscription_ = this->create_subscription<px4_msgs::msg::VehicleLocalPosition>(
            "/fmu/out/vehicle_local_position_v1",
            qos, std::bind(&ExecuteTrajectory::vehicle_local_position_callback, this, std::placeholders::_1));

        attitude_subscription_ = this->create_subscription<px4_msgs::msg::VehicleAttitude>(
            "/fmu/out/vehicle_attitude",
            qos, std::bind(&ExecuteTrajectory::vehicle_attitude_callback, this, std::placeholders::_1));

        // Publishers
        offboard_control_mode_publisher_ = this->create_publisher<px4_msgs::msg::OffboardControlMode>(
            "/fmu/in/offboard_control_mode", 10);

        trajectory_setpoint_publisher_ = this->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
            "/fmu/in/trajectory_setpoint", 10);

        vehicle_command_publisher_ = this->create_publisher<px4_msgs::msg::VehicleCommand>(
            "/fmu/in/vehicle_command", 10);

        timer_offboard_ = this->create_wall_timer(100ms, std::bind(&ExecuteTrajectory::activate_offboard, this));
        timer_trajectory_publish_ = this->create_wall_timer(20ms, std::bind(&ExecuteTrajectory::publish_trajectory_setpoint, this));
    }

private:
    rclcpp::Subscription<px4_msgs::msg::VehicleLocalPosition>::SharedPtr local_position_subscription_;
    rclcpp::Subscription<px4_msgs::msg::VehicleAttitude>::SharedPtr attitude_subscription_;
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_control_mode_publisher_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_command_publisher_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_setpoint_publisher_;

    rclcpp::TimerBase::SharedPtr timer_offboard_;
    rclcpp::TimerBase::SharedPtr timer_trajectory_publish_;

    bool offboard_active{false};
    bool trajectory_generated{false};
    bool landing_requested_{false};

    // Temporal Parameters
    double total_time_ = 50.0;  // Total trajectory time (seconds)
    double t_elapsed_ = 0.0;
    double offboard_counter{0};

    // Vehicle Data
    VehicleLocalPosition current_position_{};
    VehicleAttitude current_attitude_{};

    // 4D Spline (X, Y, Z, Yaw) cubic
    typedef Eigen::Spline<double, 4> Spline4d;
    Spline4d spline_;

    void vehicle_local_position_callback(const px4_msgs::msg::VehicleLocalPosition::SharedPtr msg)
    {
        current_position_ = *msg;
    }

    void vehicle_attitude_callback(const px4_msgs::msg::VehicleAttitude::SharedPtr msg)
    {
        current_attitude_ = *msg;
    }

    void generate_spline_trajectory()
    {
        // 7 waypoints: 4 rows (x,y,z,yaw) x 7 columns
        Eigen::MatrixXd points(4, 7);

        double start_yaw = utilities::quatToRpy(Eigen::Vector4d(
            current_attitude_.q[0], current_attitude_.q[1],
            current_attitude_.q[2], current_attitude_.q[3]))(2);

        double x0 = current_position_.x;
        double y0 = current_position_.y;

        // Waypoint 0: Start position
        points.col(0) << x0, y0, -3.0, start_yaw;

        // Waypoint 1: Move forward-right and climb
        points.col(1) << x0 + 6.0, y0 + 3.0, -7.0, start_yaw + 0.3;

        // Waypoint 2: Move left and climb more
        points.col(2) << x0 + 2.0, y0 + 10.0, -12.0, start_yaw + 0.8;

        // Waypoint 3: Move back-right and descend slightly
        points.col(3) << x0 + 9.0, y0 + 6.0, -9.0, start_yaw + 1.5;

        // Waypoint 4: Move forward-left and climb
        points.col(4) << x0 - 4.0, y0 + 12.0, -14.0, start_yaw + 2.2;

        // Waypoint 5: Move back and descend
        points.col(5) << x0 - 6.0, y0 + 4.0, -8.0, start_yaw + 2.8;

        // Waypoint 6: Return near start, low altitude
        points.col(6) << x0 + 1.0, y0 + 1.0, -4.0, start_yaw + 3.14;

        // Cubic B-Spline interpolation
        spline_ = Eigen::SplineFitting<Spline4d>::Interpolate(points, 3);

        trajectory_generated = true;
        t_elapsed_ = 0.0;

        std::cout << "Trajectory generated with 7 waypoints." << std::endl;
    }

    void activate_offboard()
    {
        if (landing_requested_)
        {
            return;
        }

        if (offboard_counter == 10)
        {
            if (!trajectory_generated)
            {
                generate_spline_trajectory();
            }

            VehicleCommand msg{};
            msg.param1 = 1;
            msg.param2 = 6;
            msg.command = VehicleCommand::VEHICLE_CMD_DO_SET_MODE;
            msg.target_system = 1;
            msg.target_component = 1;
            msg.source_system = 1;
            msg.source_component = 1;
            msg.from_external = true;
            msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
            vehicle_command_publisher_->publish(msg);

            msg.command = VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM;
            msg.param1 = 1.0;
            vehicle_command_publisher_->publish(msg);

            offboard_active = true;
            std::cout << "Offboard activated & Vehicle Armed." << std::endl;
        }

        OffboardControlMode msg{};
        msg.position = true;
        msg.velocity = true;
        msg.acceleration = true;
        msg.attitude = false;
        msg.body_rate = false;
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        offboard_control_mode_publisher_->publish(msg);

        if (offboard_counter < 11)
            offboard_counter++;
    }

    void publish_trajectory_setpoint()
    {
        if (!offboard_active || !trajectory_generated || landing_requested_)
        {
            return;
        }

        double u = t_elapsed_ / total_time_;

        if (u >= 1.0)
        {
            std::cout << "Trajectory finished. Landing..." << std::endl;

            VehicleCommand msg{};
            msg.command = VehicleCommand::VEHICLE_CMD_NAV_LAND;
            msg.target_system = 1;
            msg.target_component = 1;
            msg.source_system = 1;
            msg.source_component = 1;
            msg.from_external = true;
            msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
            vehicle_command_publisher_->publish(msg);

            landing_requested_ = true;
            return;
        }

        auto values = spline_.derivatives(u, 2);

        double dt_inv = 1.0 / total_time_;
        double dt2_inv = dt_inv * dt_inv;

        Eigen::Vector4d pos = values.col(0);
        Eigen::Vector4d vel = values.col(1) * dt_inv;
        Eigen::Vector4d acc = values.col(2) * dt2_inv;

        TrajectorySetpoint msg{};
        msg.position = {float(pos(0)), float(pos(1)), float(pos(2))};
        msg.velocity = {float(vel(0)), float(vel(1)), float(vel(2))};
        msg.acceleration = {float(acc(0)), float(acc(1)), float(acc(2))};
        msg.yaw = float(pos(3));
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        trajectory_setpoint_publisher_->publish(msg);

        t_elapsed_ += 0.02;
    }
};

int main(int argc, char *argv[])
{
    std::cout << "Starting Trajectory Node..." << std::endl;
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ExecuteTrajectory>());
    rclcpp::shutdown();
    return 0;
}
