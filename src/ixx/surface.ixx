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
#include <unordered_map>
#include <any>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:surface;
// import :display;
import :config;
export namespace egl {
class Display;
class Surface {
 public:
	enum struct Attribute : EGLenum {
		GL_COLORSPACE = EGL_GL_COLORSPACE,
		RENDER_BUFFER = EGL_RENDER_BUFFER,
		VG_ALPHA_FORMAT = EGL_VG_ALPHA_FORMAT,
		VG_COLORSPACE = EGL_VG_COLORSPACE
	};
	static auto CreateWindow(
		const Display& display,
		const Config& config,
		NativeWindowType native_window,
		const std::unordered_map<Attribute, EGLint>& attrib_list = {}) -> Surface;
	constexpr auto GetHandle() const noexcept -> const EGLSurface&;
	auto Attrib(
		EGLint attribute,
		EGLint value) -> EGLBoolean;
	EGLBoolean Query(
		EGLint attribute,
		EGLint* value);
	void SwapBuffers();
 private:
	EGLSurface handle{};
	std::reference_wrapper<std::add_const_t<Display>> display;
	explicit Surface(const EGLSurface& handle, const Display& display);
};
} // namespace egl
namespace egl {
constexpr auto Surface::GetHandle() const noexcept -> const EGLSurface& {
	return this->handle;
}
} // namespace egl