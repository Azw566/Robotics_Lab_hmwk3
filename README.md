# RL2025HW03 :package:
Fly your drone

## Getting Started :hammer:
Make sure you have installed `QGROUNDCONTROL` available [here](https://qgroundcontrol.com)

```shell
cd /ros2_ws/src
git clone https://github.com/Azw566/Robotixs_Lab_hmwk3
cd PX4-Autopilot
colcon build 
source install/setup.bash
```

## Usage :white_check_mark:

 ## **1.Fly custom** 
Open `QGROUNDCONTROL` then in a new terminal:
```shell
cd /ros2_ws/src/PX4-Autopilot/
make px4_sitl gz_custom
```
A new gazebo simulation will open and from now you can fly your drone by using the sticks. 

 ## **2.Force land revisited** :arrows_clockwise:
Open `QGROUNDCONTROL` then in a new terminal:
```shell
cd /ros2_ws/src/PX4-Autopilot/
make px4_sitl gz_custom
```
In a second terminal run the following command:
```shell
cd /ros2_ws/src
./DDS_run.sh
```
And in a third terminal launch:
```shell
cd /ros2_ws
ros2 run force_land force_land
```
From now, you can takeoff your drone. The landing procedure will activate only once after a little delay to allow you to free the joystick without canceling the landing phase, after that the threshold of 20m is surpassed. 

To test the correct functioning, it is advisable to do the takeoff directly above 20 m, and then resume control by using the sticks. 

## **3. Flying in offboard mode** :airplane:
Open `QGROUNDCONTROL` then in a new terminal:
```shell
cd /ros2_ws/src/PX4-Autopilot/
make px4_sitl gz_x500
```
In a second terminal run the following command:
```shell
cd /ros2_ws/src
./DDS_run.sh
```
And in a third terminal launch:
```shell
cd /ros2_ws
ros2 run offboard_rl execute_trajectory
```
Then you can see, the following the trajectory.

