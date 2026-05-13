#include "ClassPhotometric.hpp"
#include "jsonKey.hpp"
#include <cstddef>
#include <vector>

/*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

PhotometricStereo::PhotometricCompute::PhotometricCompute() {}

std::vector<cv::Mat> PhotometricStereo::PhotometricCompute::_normalizeImages(
    cv::Size sizeArray, size_t lights,
    const std::vector<cv::Mat> imagesGrayScale) {
  std::vector<cv::Mat> tmp;
  for (size_t i = 0; i < lights; ++i) {
    cv::Mat img = cv::Mat::zeros(sizeArray, CV_32F);
    cv::normalize(imagesGrayScale[i], img, 0, 255, cv::NORM_MINMAX, CV_32F);
    tmp.push_back(img);
  }
  return tmp;
}

std::vector<cv::Mat> PhotometricStereo::PhotometricCompute::_computeG(
    cv::Size sizeArray, size_t lights,
    const std::vector<cv::Mat> imagesGrayScaleNorm_I,
    const std::vector<cv::Mat> lightDirectionsInv) {
  std::vector<cv::Mat> tmp;
  for (int j = 0; j < 3; ++j) {
    cv::Mat component = cv::Mat::zeros(sizeArray, CV_32F);
    for (size_t i = 0; i < lights; ++i) {
      component +=
          imagesGrayScaleNorm_I[i] * lightDirectionsInv[i].at<float>(j);
    }
    tmp.push_back(component);
  }
  return tmp;
}

cv::Mat PhotometricStereo::PhotometricCompute::_computeGmagnitudeEcludian(
    const std::vector<cv::Mat> &g) {
  cv::Mat somma = cv::Mat::zeros(g[0].size(), CV_32F);
  cv::Mat magitude;
  for (size_t j = 0; j < g.size(); ++j) {
    cv::Mat sq;
    cv::multiply(g[j], g[j], sq);
    somma += sq;
  }
  cv::sqrt(somma, magitude);
  return magitude;
}

// cv::Mat PhotometricCompute::_preProcessForVisualization(visualizeFlags flags)
// {
//   cv::Mat toShow;
//   if (flags == ALBEDO) {
//     cv::normalize(this->_gMagnitudes, toShow, 0, 255, cv::NORM_MINMAX,
//     CV_8U); return toShow;
//   }
//   if (flags == NORMAL_MAP) {
//     toShow = (this->_normalMap + 1) / 2;
//     return toShow;
//   }
//   return toShow;
// }

// void PhotometricCompute::visualizeImage(visualizeFlags flags) {
//   cv::Mat toShow = this->_preProcessForVisualization(flags);
//   cv::imshow("Image", toShow);
//   cv::waitKey(0);
// }

cv::Mat PhotometricStereo::PhotometricCompute::_computeNormalMap(
    cv::Size sizeArray, const std::vector<cv::Mat> &g,
    const cv::Mat &gMagnitudes) {
  cv::Mat normalMap;
  cv::Mat normalMapX = cv::Mat::zeros(sizeArray, CV_32F);
  cv::Mat normalMapY = cv::Mat::zeros(sizeArray, CV_32F);
  cv::Mat normalMapZ = cv::Mat::zeros(sizeArray, CV_32F);
  cv::Mat pOne;
  cv::divide(1, gMagnitudes, pOne);
  cv::multiply(g[0], pOne, normalMapX);
  cv::multiply(g[1], pOne, normalMapY);
  cv::multiply(g[2], pOne, normalMapZ);
  std::vector<cv::Mat> channels = {normalMapZ, normalMapY, normalMapX};
  cv::merge(channels, normalMap);
  return normalMap;
}

std::vector<cv::Mat>
PhotometricStereo::PhotometricCompute::_computeLightDirectionsInv(
    size_t lights, const std::vector<cv::Mat> &lightDirections) {
  std::vector<cv::Mat> lightDirectionsInv;
  for (size_t i = 0; i < lights; ++i) {
    lightDirectionsInv.push_back(lightDirections[i].inv(cv::DECOMP_SVD));
  }
  return lightDirectionsInv;
}
void PhotometricStereo::PhotometricCompute::computeAlbedoGreyScale() {}
void PhotometricStereo::PhotometricCompute::computeAlbedoColor() {}

std::vector<cv::Mat> PhotometricStereo::PhotometricCompute::computeG(
    const std::vector<cv::Mat> &imagesGrayScale,
    const std::vector<cv::Mat> &lightDirections) {
  cv::Size sizeArray = imagesGrayScale[0].size();
  size_t lights = imagesGrayScale.size();
  std::vector<cv::Mat> imagesGrayScaleNorm_I =
      this->_normalizeImages(sizeArray, lights, imagesGrayScale);
  std::vector<cv::Mat> lightDirectionsInv =
      this->_computeLightDirectionsInv(lights, lightDirections);
  std::vector<cv::Mat> g = this->_computeG(
      sizeArray, lights, imagesGrayScaleNorm_I, lightDirectionsInv);
  return g;
}

cv::Mat PhotometricStereo::PhotometricCompute::computeGMagnitudes(
    const std::vector<cv::Mat> &g) {
  cv::Mat gMagnitudes = this->_computeGmagnitudeEcludian(g);
  return gMagnitudes;
}

void PhotometricStereo::PhotometricCompute::computeNormalMap(
    const std::vector<cv::Mat> &g, const cv::Mat &gMagnitudes) {
  cv::Mat normalMap =
      this->_computeNormalMap(gMagnitudes.size(), g, gMagnitudes);
}

/*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::PhotometricCompute::~PhotometricCompute() {}