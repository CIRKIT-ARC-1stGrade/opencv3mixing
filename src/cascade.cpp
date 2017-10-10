#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <opencv2/objdetect/objdetect.hpp>

class CascadeDetector {
public:
  CascadeDetector();
  void cascade(const sensor_msgs::ImageConstPtr& msg);
private:
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;
  image_transport::ImageTransport it_;
  image_transport::ImageTransport pit_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
};

CascadeDetector::CascadeDetector()
  : nh_{},
    pnh_{"~"},
    it_{nh_},
    pit_{pnh_},
    image_sub_{it_.subscribe("src_image", 1, &CascadeDetector::cascade, this)},
    image_pub_{pit_.advertise("dest_image", 1)}
{ 
}

void CascadeDetector::cascade(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr src_img{cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8)};
  double scale = 2.0;
  cv::Mat small_img{cv::saturate_cast<int>(src_img->image.rows/scale), cv::saturate_cast<int>(src_img->image.cols/scale), CV_8UC1};
  cv::resize(src_img->image, small_img, small_img.size(), 0, 0, cv::INTER_NEAREST);
  image_pub_.publish(cv_bridge::CvImage{std_msgs::Header{}, "mono8", small_img}.toImageMsg());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cascade_node");
  CascadeDetector tester{};
  ros::spin();
  return 0;
}
