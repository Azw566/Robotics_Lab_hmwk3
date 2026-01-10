#include <memory>
#include <chrono>
#include <functional>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/executors/multi_threaded_executor.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class JointStateSubscriber : public rclcpp::Node
{
public:
  JointStateSubscriber()
  : Node("joint_state_subscriber")
  {
    subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "/joint_states", 10,
      std::bind(&JointStateSubscriber::topic_callback, this, _1)
    );
  }

private:
  void topic_callback(const sensor_msgs::msg::JointState & msg) const
  {
    for (size_t i = 0; i < std::min((size_t)4, msg.position.size()); i++)
    {
      RCLCPP_INFO(this->get_logger(), "The joint %zu: %.3f", i+1, msg.position[i]);
    }
  }

  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
};

class RobotControllerNode : public rclcpp::Node
{
public:
  RobotControllerNode() : Node("robot_controller_node"), step_index_(0)
  {
    // Initialize controller mode parameter
    this->declare_parameter("use_trajectory_mode", false);
    trajectory_mode_ = this->get_parameter("use_trajectory_mode").as_bool();

    // Define target positions for the robot joints
    joint_target_positions_ = {
      {0.0, 0.0, 0.0, 1.0},
      {0.7, 0.0, 0.7, 1.0},
      {0.7, -1.0, 0.7, 0.0},
      {0.0, 0.0, 0.0, 0.0}
    };

    // Set up appropriate publisher based on control mode
    if (trajectory_mode_) {
      trajectory_publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
        "/trajectory_controller/commands", 10);
      RCLCPP_INFO(this->get_logger(), "Trajectory control mode activated");
    } else {
      position_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
        "/position_controller/commands", 10);
      RCLCPP_INFO(this->get_logger(), "Position control mode activated");
    }

    // Create timer for periodic position updates
    update_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(5000),
      std::bind(&RobotControllerNode::update_joints, this)
    );
  }

private:
  void update_joints()
  {
    const auto& target = joint_target_positions_[step_index_];

    if (trajectory_mode_) {
      // Publish trajectory message
      auto trajectory = trajectory_msgs::msg::JointTrajectory();
      trajectory.joint_names = {"joint_0", "joint_1", "joint_2", "joint_3"};
      trajectory.points.push_back({});
      trajectory.points.back().positions = target;
      trajectory.points.back().time_from_start = rclcpp::Duration(5s);
      trajectory_publisher_->publish(trajectory);
      RCLCPP_INFO(this->get_logger(), "Published trajectory step %d", step_index_);
    } else {
      // Publish position command
      auto command = std_msgs::msg::Float64MultiArray();
      command.data = target;
      position_publisher_->publish(command);
      RCLCPP_INFO(this->get_logger(), "Published position step %d", step_index_);
    }

    // Increment step counter (wraps around automatically)
    step_index_ = (step_index_ + 1) % joint_target_positions_.size();
  }

  size_t step_index_;
  bool trajectory_mode_;
  rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr trajectory_publisher_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr position_publisher_;
  std::vector<std::vector<double>> joint_target_positions_;
  rclcpp::TimerBase::SharedPtr update_timer_;
};

  bool use_trajectory_;
  size_t current_step_;
  std::vector<std::vector<double>> target_pos_;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_pos_;
  rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_traj_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto joint_sub = std::make_shared<JointStateSubscriber>();
  auto controller_pub = std::make_shared<ControllerPublisher>();

  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(joint_sub);
  executor.add_node(controller_pub);
  executor.spin();

  rclcpp::shutdown();
  return 0;
}
