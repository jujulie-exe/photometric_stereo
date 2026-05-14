#include "ClassService.hpp"
#include "opencv2/highgui.hpp"
Service::Service() {}
void Service::visualizeImages(const cv::Mat &images) {
  cv::imshow("Images", images);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

void Service::saveImage(const cv::Mat &images, const std::string &path) {
  cv::imwrite(path, images);
}
Service::~Service() {}