#ifndef PHOTOMETRIC_STEREO_HPP
#define PHOTOMETRIC_STEREO_HPP

#include "Depencies.hpp"

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
  /*
   * ORCHESTRATOR
   */

public:
  enum visualizeFlags {
    ALBEDO = 1,
    NORMAL_MAP = 2,
    GRADIENT = 4,
  };

  /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  PhotometricStereo();
  PhotometricStereo(PhotometricStereo const &src) = delete;

  /*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  // Esempio: cv::Mat getNormalMap() const;

  /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  void run(const json &config);
  // Esempio: void compute();

  /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  PhotometricStereo &operator=(PhotometricStereo const &rsh) = delete;

  /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  virtual ~PhotometricStereo();

private:
  struct PhotometricLoad {
    static std::vector<cv::Mat> loadImagesGreyScale(const json &config,
                                                    size_t nbrLights);
    static std::vector<cv::Mat> chargeLightDirections(size_t lights,
                                                      const json &config);
    static std::vector<cv::Mat> loadImagesRGB(const json &config,
                                              size_t nbrLights);
    static std::vector<std::vector<cv::Mat>>
    loadImagesSplitRGB(const json &config);
  };

  struct Transform {
    static std::vector<cv::Mat>
    RGBtoGreyScale(const std::vector<cv::Mat> &imagesRGB);
  };

  class PhotometricCompute {

  public:
    PhotometricCompute();
    ~PhotometricCompute();
    void computeNormalMap(const std::vector<cv::Mat> &g,
                          const cv::Mat &gMagnitudes);
    void computeAlbedoGreyScale();
    void computeAlbedoColor();
    cv::Mat computeGMagnitudes(const std::vector<cv::Mat> &g);
    std::vector<cv::Mat> computeG(const std::vector<cv::Mat> &imagesGrayScale,
                                  const std::vector<cv::Mat> &lightDirections);

  private:
    // TODO funzione di trasformaione da RGB a GreyScale
    std::vector<cv::Mat>
    _normalizeImages(cv::Size sizeArray, size_t lights,
                     const std::vector<cv::Mat> imagesGrayScale);
    std::vector<cv::Mat>
    _computeLightDirectionsInv(size_t lights,
                               const std::vector<cv::Mat> &lightDirections);
    std::vector<cv::Mat>
    _computeG(cv::Size sizeArray, size_t lights,
              const std::vector<cv::Mat> imagesGrayScaleNorm_I,
              const std::vector<cv::Mat> lightDirectionsInv);
    cv::Mat _computeGmagnitudeEcludian(const std::vector<cv::Mat> &g);
    cv::Mat _computeNormalMap(cv::Size sizeArray, const std::vector<cv::Mat> &g,
                              const cv::Mat &gMagnitudes);
  };
  /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

  /*♡♡♡♡♡♡♡♡♡♡♡VARIABLE♡♡♡♡♡♡♡♡♡♡♡♡♡*/
  unsigned int _size;
  size_t _numLights;
  json _config;
  PhotometricCompute _compute;

  /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/

  class InvalidInput : public std::exception {
    virtual const char *what() const throw();
  };
};

#endif
