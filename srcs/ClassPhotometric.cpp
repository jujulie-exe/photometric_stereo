#include "ClassPhotometric.hpp"

/*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::PhotometricStereo(const json &config) {}

/*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricResult PhotometricStereo::getResult() const { return _result; }

void PhotometricStereo::run() {
  this->_compute.computeNormalMap();
  this->_compute.computeAlbedo();
  this->_compute.computeGradient();
}

/*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

/*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
PhotometricStereo::~PhotometricStereo() {}