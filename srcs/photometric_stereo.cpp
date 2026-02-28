#include "photometric_stereo.hpp"
#include "jsonKey.hpp"
#include <cstddef>

/*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::PhotometricStereo() : _size(0) {}

PhotometricStereo::PhotometricStereo(const json &config) {
  this->_imagesGrayScaleNorm_I.clear();
  this->_numLights = config[ConfigKeys::LIGHTS_CONFIGURATION].size();
  this->_config = config;
  for (size_t i = 0; i < this->_numLights; ++i) {
    this->_imagesGrayScale.push_back(cv::imread(
        config[ConfigKeys::LIGHTS_CONFIGURATION][i][ConfigKeys::Lights::FILE],
        cv::IMREAD_GRAYSCALE));
  }
  this->_normalizeImages();
  this->_chargeLightDirections();
  this->_chargeLightDirectionsInv();
  this->_computeG();
  this->_computeGmagnitudeEcludian();
  this->_computeNormalMap();
}

void PhotometricStereo::_normalizeImages() {
  cv::Mat img = cv::Mat::zeros(this->_imagesGrayScale[0].size(), CV_32F);
  for (size_t i = 0; i < this->_numLights; ++i) {
    cv::normalize(this->_imagesGrayScale[i], img, 0, 255, cv::NORM_MINMAX,
                  CV_32F);
    this->_imagesGrayScaleNorm_I.push_back(img.clone());
  }
}

void PhotometricStereo::_computeG() {
  this->_g.clear();
  for (int j = 0; j < 3; ++j) {
    cv::Mat component =
        cv::Mat::zeros(this->_imagesGrayScaleNorm_I[0].size(), CV_32F);
    for (size_t i = 0; i < this->_numLights; ++i) {
      component += this->_imagesGrayScaleNorm_I[i] *
                   this->_lightDirectionsInv[i].at<float>(j);
    }
    this->_g.push_back(component);
  }
}

void PhotometricStereo::_computeGmagnitudeEcludian() {
  cv::Mat somma = cv::Mat::zeros(this->_g[0].size(), CV_32F);
  for (size_t j = 0; j < this->_g.size(); ++j) {
    cv::Mat sq;
    cv::multiply(this->_g[j], this->_g[j], sq);
    somma += sq;
  }
  cv::sqrt(somma, this->_gMagnitudes);
}

void PhotometricStereo::_chargeLightDirections() {
  this->_lightDirections.clear();
  for (size_t i = 0; i < this->_numLights; ++i) {
    cv::Mat raw(1, 3, CV_32F);
    raw.at<float>(0) = this->_config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                                    [ConfigKeys::Lights::DIRECTION][0];
    raw.at<float>(1) = this->_config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                                    [ConfigKeys::Lights::DIRECTION][1];
    raw.at<float>(2) = this->_config[ConfigKeys::LIGHTS_CONFIGURATION][i]
                                    [ConfigKeys::Lights::DIRECTION][2];
    this->_lightDirections.push_back(raw);
  }
}
cv::Mat PhotometricStereo::_preProcessForVisualization(visualizeFlags flags) {
  cv::Mat toShow;
  if (flags == ALBEDO) {
    cv::normalize(this->_gMagnitudes, toShow, 0, 255, cv::NORM_MINMAX, CV_8U);
    return toShow;
  }
  if (flags == NORMAL_MAP) {
    toShow = (this->_normalMap + 1) / 2;
    return toShow;
  }
  return toShow;
}

void PhotometricStereo::visualizeImage(visualizeFlags flags) {
  cv::Mat toShow = this->_preProcessForVisualization(flags);
  cv::imshow("Image", toShow);
  cv::waitKey(0);
}

void PhotometricStereo::_computeNormalMap() {
  cv::Mat normalMapX =
      cv::Mat::zeros(this->_imagesGrayScaleNorm_I[0].size(), CV_32F);
  cv::Mat normalMapY =
      cv::Mat::zeros(this->_imagesGrayScaleNorm_I[0].size(), CV_32F);
  cv::Mat normalMapZ =
      cv::Mat::zeros(this->_imagesGrayScaleNorm_I[0].size(), CV_32F);
  cv::Mat pOne;
  cv::divide(1, this->_gMagnitudes, pOne);
  cv::multiply(this->_g[0], pOne, normalMapX);
  cv::multiply(this->_g[1], pOne, normalMapY);
  cv::multiply(this->_g[2], pOne, normalMapZ);
  std::vector<cv::Mat> channels = {normalMapZ, normalMapY, normalMapX};
  cv::merge(channels, this->_normalMap);
}

void PhotometricStereo::_chargeLightDirectionsInv() {
  this->_lightDirectionsInv.clear();
  for (size_t i = 0; i < this->_numLights; ++i) {
    this->_lightDirectionsInv.push_back(
        this->_lightDirections[i].inv(cv::DECOMP_SVD));
  }
}

/*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::~PhotometricStereo() {}

/*♡♡♡♡♡♡♡♡♡♡♡EXCEPTIONS♡♡♡♡♡♡♡♡♡♡♡♡♡*/
const char *PhotometricStereo::InvalidInput::what() const throw() {
  return "Invalid input for PhotometricStereo";
}