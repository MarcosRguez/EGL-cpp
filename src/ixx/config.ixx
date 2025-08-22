/**
 * @file config.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:config;
export namespace egl {
class Config {
 public:
	constexpr auto GetHandle() const noexcept -> const EGLConfig&;
 private:
	EGLConfig handle{};
};
} // namespace egl
namespace egl {
constexpr auto Config::GetHandle() const noexcept -> const EGLConfig& {
	return this->handle;
}
} // namespace egl