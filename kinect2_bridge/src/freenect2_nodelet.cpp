#include <kinect2_bridge/freenect2_bridge.h>
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

namespace freenect2_camera {

  class Freenect2Nodelet : public nodelet::Nodelet {

  public:
    virtual void onInit()
    {
      nodelet.reset(new Freenect2Bridge(getMTNodeHandle(), getPrivateNodeHandle()));
    };

    boost::shared_ptr<Freenect2Bridge> nodelet;

  };

}

PLUGINLIB_DECLARE_CLASS(freenect2_camera, Freenect2Nodelet, freenect2_camera::Freenect2Nodelet, nodelet::Nodelet);
