#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <control_trajectory_execution/control_trackingAction.h>
#include <trajectory_custom_msgs/PointStampedArray.h>

trajectory_custom_msgs::PointStampedArray control_points;
bool points_received = false;
float xOffset, yOffset, zOffset;