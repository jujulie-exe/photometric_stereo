
#ifndef SERVICE_HPP
#define SERVICE_HPP
#include "Depencies.hpp"
#include "opencv2/core/mat.hpp"
class Service {
public:
  Service();
  void visualizeImages(const cv::Mat &images);
  void saveImage(const cv::Mat &images, const std::string &path);
  virtual ~Service();

private:
  Service(Service const &) = delete;
  Service &operator=(Service const &rsh) = delete;
};
#endif
