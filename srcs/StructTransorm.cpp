#include "ClassPhotometric.hpp"

std::vector<cv::Mat> PhotometricStereo::Transform::RGBtoGreyScale(
    const std::vector<cv::Mat> &imagesRGB) {
  std::vector<cv::Mat> imagesGrayScale;
  for (size_t i = 0; i < imagesRGB.size(); ++i) {
    cv::Mat imgGrayScale;
    cv::cvtColor(imagesRGB[i], imgGrayScale, cv::COLOR_BGR2GRAY);
    imagesGrayScale.push_back(imgGrayScale);
  }
  return imagesGrayScale;
}