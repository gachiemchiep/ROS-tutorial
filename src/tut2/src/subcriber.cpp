/*
 * subcriber.cpp
 *
 *  Created on: May 5, 2019
 *      Author: gachiemchiep
 */

#include <ros/ros.h>
#include <std_msgs/String.h>

void chatterCallbackk(const std_msgs::String::ConstPtr& msg) {
	ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "Subcriber");

	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("msg", 1000, chatterCallbackk);

	ros::spin();

	return 0;
}


