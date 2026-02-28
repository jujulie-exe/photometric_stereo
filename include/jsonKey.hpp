#ifndef JSONKEY_HPP
#define JSONKEY_HPP

namespace ConfigKeys {

constexpr const char *SESSION_NAME = "session_name";
constexpr const char *NUM_LIGHTS = "num_lights";
constexpr const char *LIGHTS_CONFIGURATION = "lights_configuration";

namespace Lights {
constexpr const char *FILE = "file";
constexpr const char *DIRECTION = "direction";
} // namespace Lights

constexpr const char *ALGORITHM_PARAMS = "algorithm_params";
namespace AlgorithmParams {
constexpr const char *GAMMA_CORRECTION = "gamma_correction";
constexpr const char *SHADOW_THRESHOLD = "shadow_threshold";
} // namespace AlgorithmParams

// Compatibility keys for existing code
constexpr const char *NBR_LIGHT_DIRCTION = "num_lights";
constexpr const char *LIGHT_DIRCTION = "lights_configuration";

} // namespace ConfigKeys

#endif // JSONKEY_HPP
