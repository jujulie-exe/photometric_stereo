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
std::vector<std::vector<cv::Mat>>
PhotometricStereo::Transform::splitter(const std::vector<cv::Mat> &imagesRGB) {
  std::vector<cv::Mat> imagesSplit_channel_1;
  std::vector<cv::Mat> imagesSplit_channel_2;
  std::vector<cv::Mat> imagesSplit_channel_3;
  for (size_t i = 0; i < imagesRGB.size(); ++i) {
    std::vector<cv::Mat> channels;
    cv::split(imagesRGB[i], channels);
    imagesSplit_channel_1.push_back(channels[0]);
    imagesSplit_channel_2.push_back(channels[1]);
    imagesSplit_channel_3.push_back(channels[2]);
  }
  return std::vector<std::vector<cv::Mat>>(
      {imagesSplit_channel_1, imagesSplit_channel_2, imagesSplit_channel_3});
}