#ifndef WRAPPER_PHOTOMETRIC_RESULT_HPP
#define WRAPPER_PHOTOMETRIC_RESULT_HPP

#include "ClassPhotometric.hpp"
#include "Depencies.hpp"
using json = nlohmann::json;
class PhotometricResult {
public:
  PhotometricResult();
  ~PhotometricResult();

private:
  const cv::Mat _albedo;
  const cv::Mat _normalMap;
  const cv::Mat _gradient;
  const cv::Mat _imagesGrayScaleNorm_I;
  const cv::Mat _g;
  const cv::Mat _gMagnitudes;
  const std::vector<cv::Mat> _lightDirections;
  const std::vector<cv::Mat> _lightDirectionsInv;
  const std::vector<cv::Mat> _imagesGrayScale;
  const size_t _numLights;
  const json _config;
};

#endif