#include "control_trajectory_execution_action_client.h"


void callback(trajectory_custom_msgs::PointStampedArray waypoints){
	ROS_INFO("Received the points");
	for (int i=0; i<waypoints.points.size(); i++){
		control_points.points.push_back(waypoints.points[i]);
	}
	points_received = true;
}

void doneCb (const actionlib::SimpleClientGoalState& state, const control_trajectory_execution::control_trackingResultConstPtr& result){
	ROS_INFO("Finished in state [%s]", state.toString().c_str());
	ros::shutdown();
}

void activeCb (){
	ROS_INFO("Just went active");
}

void feedbackCb (const control_trajectory_execution::control_trackingFeedbackConstPtr& feedback){
	ROS_INFO("The portion of the trajectory that has been executed is %f", feedback->percentage);
}

int main(int argc, char** argv){
	ros::init(argc, argv, "control_trajectory_execution_action_client");
	ros::AsyncSpinner spinner(2);
	ros::NodeHandle nh;

	spinner.start();
	actionlib::SimpleActionClient<control_trajectory_execution::control_trackingAction>	ac("control_tracking", true);
	ros::Subscriber sub = nh.subscribe("/candidate_points", 10, callback);
	while (ros::ok()){
		if (points_received){
			ROS_INFO("Wait for action server to start");
			ac.waitForServer();
			ROS_INFO("Action server started, sending goal");
			control_trajectory_execution::control_trackingGoal goal;
			for (int i=0; i<control_points.points.size(); i++){
				goal.waypoints.points.push_back(control_points.points[i]);
			}
			ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
			points_received = false;
		}
	}
	ros::waitForShutdown();
}