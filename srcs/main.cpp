#include "ClassPhotometric.hpp"
#include "ClassService.hpp"

int main() {
  std::ifstream f("./config.json");
  if (!f.is_open()) {
    return 1;
  }
  json data;
  try {
    data = json::parse(f, nullptr, true);
    PhotometricStereo ps = PhotometricStereo();
    const PhotometricResult &result = ps.run(data);
    Service s = Service();
    s.visualizeImages(result.getAlbedo());
    s.visualizeImages(result.getNormalMap());
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
