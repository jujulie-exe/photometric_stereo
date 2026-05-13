#include "ClassPhotometric.hpp"

std::vector<cv::Mat> PhotometricLoad::loadImagesGreyScale(const json &config,
                                                          size_t nbrLights) {
  std::vector<cv::Mat> imagesGrayScale;
  for (size_t i = 0; i < nbrLights; ++i) {
    imagesGrayScale.push_back(cv::imread(
        config[ConfigKeys::LIGHTS_CONFIGURATION][i][ConfigKeys::Lights::FILE],
        cv::IMREAD_GRAYSCALE));
  }
  return imagesGrayScale;
}

std::vector<cv::Mat> PhotometricLoad::loadImagesRGB(const json &config,
                                                    size_t nbrLights) {
  std::vector<cv::Mat> imagesRGB;
  for (size_t i = 0; i < nbrLights; ++i) {
    imagesRGB.push_back(cv::imread(
        config[ConfigKeys::LIGHTS_CONFIGURATION][i][ConfigKeys::Lights::FILE],
        cv::IMREAD_COLOR));
  }
  return imagesRGB;
}

std::vector<cv::Mat>
PhotometricLoad::chargeLightDirections(size_t lights, const json &config) {
  std::vector<cv::Mat> lightDirections;
  for (size_t i = 0; i < lights; ++i) {
    cv::Mat raw(1, 3, CV_32F);
    raw.at<float>(0) = config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                             [ConfigKeys::Lights::DIRECTION][0];
    raw.at<float>(1) = config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                             [ConfigKeys::Lights::DIRECTION][1];
    raw.at<float>(2) = config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                             [ConfigKeys::Lights::DIRECTION][2];
    lightDirections.push_back(raw);
  }
  return lightDirections;
}