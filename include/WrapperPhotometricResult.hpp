#ifndef WRAPPER_PHOTOMETRIC_RESULT_HPP
#define WRAPPER_PHOTOMETRIC_RESULT_HPP

#include "Depencies.hpp"
#include "opencv2/core/mat.hpp"
#include <vector>
using json = nlohmann::json;
class PhotometricResult {
//TODO refracotr RESULT
public:
  PhotometricResult(const cv::Mat &normalMap, const cv::Mat &albedo);
  ~PhotometricResult();

public:
  const cv::Mat &getNormalMap() const;
  const cv::Mat &getAlbedo() const;

private:
  const cv::Mat _normalMap;
  const cv::Mat _albedo;
};

#endif
