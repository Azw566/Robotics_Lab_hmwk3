# - Config file for the OpticalFlow package
# It defines the following variables
#  OpticalFlow_INCLUDE_DIRS - include directories
#  OpticalFlow_LIBRARIES    - libraries to link against
 
set(OpticalFlow_INCLUDE_DIRS "/home/telemaque/Robotics_Lab/ros2_ws/build/px4/OpticalFlow/install/include")
#set(OpticalFlow_LIBRARY_DIR "/home/telemaque/Robotics_Lab/ros2_ws/build/px4/OpticalFlow/install/lib")
FIND_LIBRARY(OpticalFlow_LIBRARIES OpticalFlow PATHS "/home/telemaque/Robotics_Lab/ros2_ws/build/px4/OpticalFlow/install/lib" NO_DEFAULT_PATH)
