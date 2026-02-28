#include "photometric_stereo.hpp"

int main() {
  std::ifstream f("./config.json");
  if (!f.is_open()) {
    return 1;
  }
  json data;
  try {
    data = json::parse(f, nullptr, true);
    PhotometricStereo ps(data);
    ps.visualizeImage(PhotometricStereo::ALBEDO);
    ps.visualizeImage(PhotometricStereo::NORMAL_MAP);
    ps.visualizeImage(PhotometricStereo::GRADIENT);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
