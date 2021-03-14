cmake_minimum_required(VERSION 3.0.2)
project(demo_motion_demonstration)


find_package(catkin REQUIRED COMPONENTS
  movement_detection
  roscpp
  rospy
  control_trajectory_execution
  trajectory_custom_msgs
  actionlib
)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES demo_HRI
#  CATKIN_DEPENDS movement_detection roscpp rospy trajectory_process_utils
#  DEPENDS system_lib
)

add_executable (control_trajectory_execution_action_client src/control_trajectory_execution_action_client.cpp)
target_link_libraries (control_trajectory_execution_action_client ${catkin_LIBRARIES})
