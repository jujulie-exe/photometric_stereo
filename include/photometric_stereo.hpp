#ifndef PHOTOMETRIC_STEREO_HPP
#define PHOTOMETRIC_STEREO_HPP

#include "external/json.hpp"
#include "jsonKey.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <set>
#include <string>
#include <vector>
using json = nlohmann::json;
/*♡♡♡♡♡♡♡♡♡♡♡COSA FARE♡♡♡♡♡♡♡♡♡♡♡♡♡
 * prende il path della foto 8 foto  quindi un array di path  lo legge con
 * cv::imread prende un json con le cordinate delle luci e il numero di luci
 *  calola la posizione p q della luce
 * calcola il gradiente di ogni pixel normalizzando a 1
 * ittera su ogni pixel il valore p q  e albedo lo mettiamo cosi da teovare I
 *
 *  formula spazio p q
 *   formula I = albedo * (L . N)
 *   formula albedo
 *
 */
class PhotometricStereo {

public:
  enum visualizeFlags {
    ALBEDO = 1,
    NORMAL_MAP = 2,
    GRADIENT = 4,
  };

  /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  PhotometricStereo(const json &config);
  PhotometricStereo(PhotometricStereo const &src) = delete;
  void visualizeImage(visualizeFlags flags);

  /*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  // Esempio: cv::Mat getNormalMap() const;

  /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  // Esempio: void compute();

  /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  PhotometricStereo &operator=(PhotometricStereo const &rsh) = delete;

  /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  virtual ~PhotometricStereo();

private:
  /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  PhotometricStereo();
  void _grayScale();
  void _chargeLightDirections();
  void _chargeLightDirectionsInv();
  void _computeG();
  void _computeGmagnitudeEcludian();
  void _normalizeImages();
  void _computeNormalMap();
  cv::Mat _preProcessForVisualization(visualizeFlags flags);

  /*♡♡♡♡♡♡♡♡♡♡♡VARIABLE♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  unsigned int _size;
  std::vector<int> _VecInt;
  std::vector<cv::Mat> _imagesGrayScale;

  std::vector<cv::Mat> _imagesGrayScaleNorm_I;
  std::vector<cv::Mat> _lightDirections;
  std::vector<cv::Mat> _lightDirectionsInv;
  size_t _numLights;
  std::vector<cv::Mat> _g;
  cv::Mat _gMagnitudes;
  cv::Mat _albedo;
  cv::Mat _normalMap;
  json _config;

  /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/

  class InvalidInput : public std::exception {
    virtual const char *what() const throw();
  };
};

#endif
