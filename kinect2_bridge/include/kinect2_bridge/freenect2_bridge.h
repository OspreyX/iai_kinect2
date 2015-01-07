#include <ros/ros.h>
#include <libfreenect2/libfreenect2.hpp>

namespace freenect2_camera {

  typedef boost::shared_ptr<libfreenect2::Freenect2Device> DevicePtr;
  typedef boost::shared_ptr<libfreenect2::FrameListener> FrameListenerPtr;

  class Freenect2Bridge {

  public:

    Freenect2Bridge(ros::NodeHandle nh, ros::NodeHandle private_nh);

  private:

    libfreenect2::Freenect2 freenect2_;
    DevicePtr device_;
    FrameListenerPtr frame_listener_;

    ros::NodeHandle nh_, private_nh_;

    ros::Timer cameraLoop_;

    std::string camera_name_;

    void setupCalibration();
  };


}