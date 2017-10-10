#include <iostream>
#include <opencv2/core/core.hpp>

int main(int argc, char** argv)
{
  constexpr double ratio{6,3};
  const cv::Mat src_image{cv::imread(argv[1], 1)};
  cv::Mat small_image{cv::saturate_cast<int>(src_image.rows/ratio), cv::saturate_cast<int>(src_image.cols/ratio), CV_8UC3};
  cv::resize(image, small_image, small_image.size(), 0, 0, cv::INTER_LINEAR);
  cv::imwrite(argv[1], image);
  return 0;
}
