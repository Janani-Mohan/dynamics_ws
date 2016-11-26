#ifndef BGAPLACEMENT_H
#define BGAPLACEMENT_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Bool.h>

class BGAPlacement
{
public:
	ros::Publisher m_orientationPub;
	ros::Subscriber m_imageSub;
	ros::Publisher m_xy_pickup_Pub;
	ros::Publisher m_xy_place_Pub;
	ros::Subscriber m_snapSub;
	geometry_msgs::Point realWorldCoords;
	void detectBGACallBack(const sensor_msgs::ImageConstPtr& img); 
	void BGACB(const std_msgs::Bool msg); 
	BGAPlacement(ros::NodeHandle n);
	
};

#endif
