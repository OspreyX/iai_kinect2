#include <kinect2_bridge/freenect2_bridge.h>
#include <ros/ros.h>

int main(int argc, char *argv[])
{

  ros::init(argc, argv, "freenect2_node");

  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");

  freenect2_camera::Freenect2Bridge node(nh, private_nh);
  ros::spin();

  return 0;

}