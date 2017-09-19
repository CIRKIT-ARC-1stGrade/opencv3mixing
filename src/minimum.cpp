#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class ImageConverter
{
  ros::NodeHandle nh_ {};
  ros::NodeHandle pnh_ {"~"};
  image_transport::ImageTransport it_ {nh_};
  image_transport::ImageTransport pit_ {pnh_};
  image_transport::Subscriber image_sub_ {it_.subscribe("input_image", 1, &ImageConverter::imageCb, this)};
  image_transport::Publisher image_pub_ {pit_.advertise("image_raw", 1)};

public:
  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    try {
      cv::Mat cv_mask;
      cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

      cv::inRange(cv_ptr->image, cv::Scalar(0, 0, 150), cv::Scalar(110, 165, 255), cv_mask); //オレンジ色検出

      image_pub_.publish(cv_mask->toImageMsg()); //cv_maskの方をパブリッシュ
    }
    catch (cv_bridge::Exception& e) {//例外処理
      ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
    }
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic {};
  ros::spin();
  return 0;
}
