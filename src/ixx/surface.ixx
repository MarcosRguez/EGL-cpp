/**
 * @file surface.ixx
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
export module egl:surface;
import :display;
import :config;
export namespace egl {
class Surface {
 public:
	static auto CreateWindow(
		const Display& display,
		const Config& config,
		NativeWindowType native_window
		// const EGLint* attrib_list
		) -> Surface;
	constexpr auto GetHandle() const noexcept -> const EGLSurface&;
 private:
	EGLSurface handle{};
};
} // namespace egl
namespace egl {
constexpr auto Surface::GetHandle() const noexcept -> const EGLSurface& {
	return this->handle;
}
} // namespace egl