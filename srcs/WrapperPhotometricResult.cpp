#include "WrapperPhotometricResult.hpp"
#include "ClassPhotometric.hpp"

PhotometricResult::PhotometricResult(
    const std::vector<cv::Mat> &gMagnitudesChannels,
    const std::vector<std::vector<cv::Mat>> &gradientChannels,
    const cv::Mat &gMagnitudesGrayScale, const std::vector<cv::Mat> &gradient,
    const cv::Mat &normalMap, const cv::Mat &albedo)

    : _gMagnitudesChannels(gMagnitudesChannels),
      _gradientChannels(gradientChannels),
      _gMagnitudesGrayScale(gMagnitudesGrayScale), _gradient(gradient),
      _normalMap(normalMap), _albedo(albedo) {
  return;
}

PhotometricResult::~PhotometricResult() { return; }

const std::vector<cv::Mat> &PhotometricResult::getGMagnitudesChannels() const {
  return this->_gMagnitudesChannels;
}
const std::vector<std::vector<cv::Mat>> &
PhotometricResult::getGradientChannels() const {
  return this->_gradientChannels;
}
const cv::Mat &PhotometricResult::getGMagnitudesGrayScale() const {
  return this->_gMagnitudesGrayScale;
}
const std::vector<cv::Mat> &PhotometricResult::getGradient() const {
  return this->_gradient;
}
const cv::Mat &PhotometricResult::getNormalMap() const {
  return this->_normalMap;
}
const cv::Mat &PhotometricResult::getAlbedo() const { return this->_albedo; }
