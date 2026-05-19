#include "ClassPhotometric.hpp"
#include "jsonKey.hpp"
#include "opencv2/core/mat.hpp"
#include <tuple>
#include <vector>

/*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::PhotometricStereo() {}

/*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡PIPELINER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
const cv::Mat PhotometricStereo::_pipelineAlbedo(const std::vector<cv::Mat> gMagnitudes) const {

  cv::Mat toShowR;
  cv::Mat toShowG;
  cv::Mat toShowB;
  cv::Mat toShow;
  cv::normalize(gMagnitudes[0], toShowR, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::normalize(gMagnitudes[1], toShowG, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::normalize(gMagnitudes[2], toShowB, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::merge(std::vector<cv::Mat>{toShowR, toShowG, toShowB}, toShow);
  return toShow;
}
const std::vector<cv::Mat> PhotometricStereo::_pipelineMultiChannelsMagnitudes(const std::vector<std::vector<cv::Mat>> imagesChannels, const std::vector<cv::Mat> lightDirections){
  std::vector<std::vector<cv::Mat>> gS;
  std::vector<cv::Mat> gMagnitudes;
  for (size_t i = 0; i < imagesChannels.size(); i++) {
    std::vector<cv::Mat> g =
        this->_compute.computeG(imagesChannels[i], lightDirections);
    gS.push_back(g);
    cv::Mat gMagnitude = this->_compute.computeGMagnitudes(g);
    gMagnitudes.push_back(gMagnitude);
  }
  return gMagnitudes;
}
const PhotometricResult PhotometricStereo::run(const json &config) {
  // load
  const std::vector<cv::Mat> imagesRGB =
      PhotometricStereo::PhotometricLoad::loadImagesRGB(
          config, config[ConfigKeys::NUM_LIGHTS]);
  // grey scale images fo normal
  const std::vector<cv::Mat> imagesGrayScale =
      PhotometricStereo::Transform::RGBtoGreyScale(imagesRGB);
  // rgb images split into channels for albedo
  const std::vector<std::vector<cv::Mat>> imagesChannels =
      PhotometricStereo::Transform::splitter(imagesRGB);
  // light direction for gradient
  const std::vector<cv::Mat> lightDirections =
      PhotometricStereo::PhotometricLoad::chargeLightDirections(
          config[ConfigKeys::NUM_LIGHTS], config);
  std::vector<cv::Mat> gMagnitudes = this->_pipelineMultiChannelsMagnitudes(imagesChannels, lightDirections);
  // compute g for each channel and magnitude for each channel
  std::vector<cv::Mat> gN =
      this->_compute.computeG(imagesGrayScale, lightDirections);
  cv::Mat gNMag = this->_compute.computeGMagnitudes(gN);
  cv::Mat normalMap = this->_compute.computeNormalMap(gN, gNMag);
  cv::Mat albedo = this->_pipelineAlbedo(gMagnitudes);
  //TODO refracotr RESULT
  std::vector<std::vector<cv::Mat>> vuoto = std::vector<std::vector<cv::Mat>>{};

  return PhotometricResult((normalMap + 1) / 2,
                           albedo);
}

/*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::~PhotometricStereo() {}
