/*
 * Camera_Node.cpp
 *
 *  Created on: May 5, 2019
 *      Author: gachiemchiep
 */

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
	// Init ROS
	ros::init(argc, argv, "Camera_Node");
	// NodeHandle
	ros::NodeHandle nh;
	// Create an Image Transport
	image_transport::ImageTransport it(nh);
	image_transport::Publisher img_pub = it.advertise("image_data", 10);

	// Open the camera
	cv::Mat img;
	cv::VideoCapture cam(0);

	// Check whether camera is usable
	if (!cam.isOpened()) {
		ROS_ERROR("Failed to open camera.");
		return -1;
	}

	// Loop rate: 30Hz
	ros::Rate loop_rate(30);

	// main loop
	int count = 0;
	while(ros::ok()) {
		// Read data from camera
		cam >> img;
		// Send camera image
		// opencv's image is in BGR uint_8 format
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),
				"bgr8", img).toImageMsg();
		img_pub.publish(msg);
		ROS_INFO("Send %d th image", count);

		ros::spinOnce();
		loop_rate.sleep();
		count++;
	}
}


