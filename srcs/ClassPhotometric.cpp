#include "ClassPhotometric.hpp"
#include "jsonKey.hpp"
#include "opencv2/core/mat.hpp"
#include <tuple>
#include <vector>

/*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::PhotometricStereo() {}

/*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/

void PhotometricStereo::run(const json &config) {
  const std::vector<std::vector<cv::Mat>> imagesChannels =
      PhotometricStereo::PhotometricLoad::loadImagesSplitRGB(config);
  const std::vector<cv::Mat> lightDirections =
      PhotometricStereo::PhotometricLoad::chargeLightDirections(
          config[ConfigKeys::NUM_LIGHTS], config);
  std::vector<std::vector<cv::Mat>> gS;
  std::vector<cv::Mat> gMagnitudes;
  // albedo
  for (size_t i = 0; i < imagesChannels.size(); i++) {
    std::vector<cv::Mat> g =
        this->_compute.computeG(imagesChannels[i], lightDirections);
    gS.push_back(g);
    cv::Mat gMagnitude = this->_compute.computeGMagnitudes(g);
    gMagnitudes.push_back(gMagnitude);
  }

  cv::Mat toShowR;
  cv::Mat toShowG;
  cv::Mat toShowB;
  cv::Mat toShow;
  cv::normalize(gMagnitudes[0], toShowR, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::normalize(gMagnitudes[1], toShowG, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::normalize(gMagnitudes[2], toShowB, 0, 255, cv::NORM_MINMAX, CV_8U);
  cv::merge(std::vector<cv::Mat>{toShowR, toShowG, toShowB}, toShow);
  cv::imshow("Albedo", toShow);
  cv::waitKey(0);
  // normal map
}

/*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::~PhotometricStereo() {}