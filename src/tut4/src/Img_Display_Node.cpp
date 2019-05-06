/*
 * Img_Display_Node.cpp
 *
 *  Created on: May 5, 2019
 *      Author: gachiemchiep
 */

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

cv::Mat image;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	try {
		image =
				cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
	}

	cv::imshow("image", image);
	cv::waitKey(1);
}

int main(int argc, char** argv) {
	// Init ROS
	ros::init(argc, argv, "Image_Display_Node");
	// NodeHandle
	ros::NodeHandle nh;

	// Read image data
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber image_sub = it.subscribe(
			"image_data", 10, imageCallback);

	ros::spin();
}
