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
#include <glad/egl.h>
export module egl:surface;
import :enums;
import :display;
// import :config;
export namespace egl {
class Display;
class Config;
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
	static auto GetCurrent(const ReadDraw& readdraw) -> Surface;
	auto Attrib(
		EGLint attribute,
		EGLint value) -> EGLBoolean;
	EGLBoolean Query(
		EGLint attribute,
		EGLint* value);
	void SwapBuffers();
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	auto ReleaseTexImage(EGLint buffer) -> EGLBoolean;
	auto CopyBuffers(NativePixmapType native_pixmap) -> bool;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	auto BindTexImage(EGLint buffer) -> bool;
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