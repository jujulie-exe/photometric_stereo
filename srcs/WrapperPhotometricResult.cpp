#include "WrapperPhotometricResult.hpp"
#include "ClassPhotometric.hpp"

PhotometricResult::PhotometricResult(
    const cv::Mat &normalMap, const cv::Mat &albedo)
  : _normalMap(normalMap), _albedo(albedo) {
  return;
}

PhotometricResult::~PhotometricResult() { return; }

const cv::Mat &PhotometricResult::getNormalMap() const {
  return this->_normalMap;
}
const cv::Mat &PhotometricResult::getAlbedo() const { return this->_albedo; }
