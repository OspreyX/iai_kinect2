#include <kinect2_bridge/freenect2_bridge.h>

namespace freenect2_camera
{

  Freenect2Bridge::Freenect2Bridge(ros::NodeHandle nh, ros::NodeHandle private_nh)
  {

    private_nh.param<std::string>("camera", camera_name_, "camera");

    std::string device_id;
    if(private_nh.getParam("device_id", device_id))
    {
      if (device_id.size() > 1 && device_id[0] == '#')
      {
        std::istringstream device_number_str(device_id.substr(1));
        int device_number;
        device_number_str >> device_number;

        if (freenect2_.enumerateDevices() < device_number)
        {
          ROS_ERROR_STREAM("Cannot access device #" << device_number << ", only " << freenect2_.enumerateDevices() <<
              "devices available");
        }
        else
        {
          // #1 refers to first device, 0-indexed
          device_.reset(freenect2_.openDevice(device_number - 1));
        }

        if (!device_)
        {
          ROS_ERROR_STREAM("Error opening device #" << device_number);
        }

      }
      else
      {
        device_.reset(freenect2_.openDevice(device_id.c_str()));
        if (!device_)
        {
          ROS_ERROR_STREAM("Error opening device with serial number " << device_id);
        }
      }
    }
    else
    {
      device_.reset(freenect2_.openDefaultDevice());
      if (!device_)
      {
        ROS_ERROR_STREAM("Failure opening default device");
      }

    }
    ROS_INFO_STREAM("Opened Freenect2 device with serial number " << device_->getSerialNumber() << " and f/w version "
        << device_->getFirmwareVersion());

    frame_listener_.reset(libfreenect2::FrameListener::create(
        libfreenect2::Frame::Color |
        libfreenect2::Frame::Ir |
        libfreenect2::Frame::Depth));
    device_->setColorFrameListener(frame_listener_.get());
    device_->setIrAndDepthFrameListener(frame_listener_.get());
    device_->start();

    libfreenect2::Freenect2Device::ColorCameraParams colorParams = device_->getColorCameraParams();
    libfreenect2::Freenect2Device::IrCameraParams irParams = device_->getIrCameraParams();

    setupCalibration();

    //must use ros timers to handle threading
//    cameraLoop_ = nh.createTimer(...)

  }

  void Freenect2Bridge::setupCalibration()
  {
    // Kinect 2 bridge reimplements camera calibration from opencv, need to switch to camera_info_manager for ROS
    // camera_calibration, reference: https://github.com/ros-drivers/camera1394/blob/master/src/nodes/driver1394.cpp#L80
  }



}
