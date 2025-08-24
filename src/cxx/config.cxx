/**
 * @file config.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 23/08/2025
 *
 *
 */
module;
#include <functional>
#include <glad/egl.h>
module egl;
namespace egl {
Config::Config(const EGLConfig& handle, const Display& display) :
		handle{handle},
		display{std::cref(display)} {}
} // namespace egl