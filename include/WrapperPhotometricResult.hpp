#ifndef WRAPPER_PHOTOMETRIC_RESULT_HPP
#define WRAPPER_PHOTOMETRIC_RESULT_HPP

#include "Depencies.hpp"
#include "opencv2/core/mat.hpp"
#include <vector>
using json = nlohmann::json;
class PhotometricResult {
public:
  PhotometricResult(const std::vector<cv::Mat> &gMagnitudesChannels,
                    const std::vector<std::vector<cv::Mat>> &gradientChannels,
                    const cv::Mat &gMagnitudesGrayScale,
                    const std::vector<cv::Mat> &gradient,
                    const cv::Mat &normalMap, const cv::Mat &albedo);
  ~PhotometricResult();

public:
  const cv::Mat &getNormalMap() const;
  const std::vector<cv::Mat> &getGradient() const;
  const cv::Mat &getAlbedo() const;
  const std::vector<std::vector<cv::Mat>> &getGradientChannels() const;
  const std::vector<cv::Mat> &getGMagnitudesChannels() const;
  const cv::Mat &getGMagnitudesGrayScale() const;

private:
  const std::vector<cv::Mat> _gMagnitudesChannels;
  const std::vector<std::vector<cv::Mat>> _gradientChannels;
  const cv::Mat _gMagnitudesGrayScale;
  const std::vector<cv::Mat> _gradient;
  const cv::Mat _normalMap;
  const cv::Mat _albedo;
};

#endif