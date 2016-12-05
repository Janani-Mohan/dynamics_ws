#include "tf_node.h"

using namespace std;
int flag1;
int flag2;
tf_node::tf_node(ros::NodeHandle n){
  tf_pub = n.advertise<geometry_msgs:: Point>("irb120/transform/pickup", 10);
  tf_pub1 = n.advertise<geometry_msgs:: Point>("irb120/transform/place", 10);
  tf_sub =  n.subscribe("/detect/bga_pickup/xy",10,&tf_node::tf_pick_broadcaster,this);
  tf_sub1 =  n.subscribe("/detect/bga_place/xy",10,&tf_node::tf_place_broadcaster,this);
  ROS_INFO("HERE");
}


void tf_node::tf_pick_broadcaster(const geometry_msgs::Point pos_msg)
{
  ROS_INFO("HERE1");
  std::string node;
  geometry_msgs:: Point pos;
  node = "/BGA_Pick";
  static tf::TransformBroadcaster br;
  tf::StampedTransform transform;
  transform.setOrigin(tf::Vector3(-pos_msg.y/1000,-pos_msg.x/1000,0.0));
  tf::Quaternion q;
  q.setRPY(0,0,0);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"/camera_link","/BGA_Pick"));
  ros::spinOnce();
  flag1 = 1;
  std::cout<<"\nPickup "<<flag1;

  try
      {
        ros::Time now = ros::Time::now();
        listener.waitForTransform("/world", "/BGA_Pick",
                              now, ros::Duration(10.0));
        listener.lookupTransform("/world", "/BGA_Pick",  
                               ros::Time(0), transform1);
        ROS_INFO("Got a transform! x = %f, y = %f",transform1.getOrigin().x(),transform1.getOrigin().y());

      }
      catch (tf::TransformException ex)
      {
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
        ros::spinOnce();
      }

    pos.x =  transform1.getOrigin().x()*1000;
    pos.y =  transform1.getOrigin().y()*1000;
    pos.z = transform1.getOrigin().z()*1000;
 
    tf_pub.publish(pos);
}

void tf_node::tf_place_broadcaster(const geometry_msgs::Point pos_msg)
{
  ROS_INFO("HERE2");
  std::string node;
  geometry_msgs:: Point pos;
  node = "/BGA_Place";
   static tf::TransformBroadcaster br;
  tf::StampedTransform transform;
  transform.setOrigin(tf::Point(pos_msg.y/1000,-pos_msg.x/1000,0.0));
  tf::Quaternion q;
  q.setRPY(0,0,0);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"/camera_link","/BGA_Place"));
  flag1 = 1;
  std::cout<<"\nPlace "<<flag1;

  try
      {
        ros::Time now = ros::Time::now();
        listener.waitForTransform("/world", "/BGA_Place",
                              now, ros::Duration(10.0));
        listener.lookupTransform("/world", "/BGA_Place",  
                               ros::Time(0), transform1);
        ROS_INFO("Got a transform! x = %f, y = %f",transform1.getOrigin().x(),transform1.getOrigin().y());

      }
      catch (tf::TransformException ex)
      {
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
      }

    pos.x =  transform1.getOrigin().x()*1000;
    pos.y =  transform1.getOrigin().y()*1000;
    pos.z = transform1.getOrigin().z()*1000;
 
    tf_pub1.publish(pos);








  // static tf::TransformBroadcaster br;
  // tf::Transform transform;
  // std::cout<<"\nx "<<pos_msg.x<<"\ny"<<pos_msg.y;
  // transform.setOrigin(tf::Vector3 (pos_msg.y/1000,-pos_msg.x/1000,0.0));
  // tf::Quaternion q1;
  // q1.setRPY(0,0,0);
  // transform.setRotation(q1);
  // br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"/camera_link","/BGA_Place"));  
  // flag2 = 1;
  // std::cout<<"\nPlace "<<flag2;
  // try
  //   {
  //       ros::Time now = ros::Time::now(); 
  //       listener.waitForTransform("/world", "/BGA_Place",
  //                             now, ros::Duration(10.0));
  //       listener.lookupTransform("/world", "/BGA_Place",  
  //                              ros::Time(0), transform3);
  //       ROS_INFO("Got a transform! x = %f, y = %f",transform3.getOrigin().x(),transform3.getOrigin().y());
  //   }
  //   catch (tf::TransformException ex)
  //   {
  //         ROS_ERROR("%s",ex.what());
  //         ros::Duration(1.0).sleep();
  //   }

  //   geometry_msgs:: Point pos1;

  //   pos1.x =  transform3.getOrigin().x()*1000;
  //   pos1.y =  transform3.getOrigin().y()*1000;
  //   pos1.z =  transform3.getOrigin().z()*1000;
 
  //   tf_pub1.publish(pos1);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "irb120_tf_calc_node");
  ros::NodeHandle node;
  tf_node work(node);
  ros::spin();
  return 0;
};