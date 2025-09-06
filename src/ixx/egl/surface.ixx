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
#include <stdexcept>
#include <utility>
#include <glad/egl.h>
export module egl:surface;
import :misc;
import :enums;
import :debug;
import :mapas;
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
	enum struct QueryAttrib : EGLenum {
		GL_COLORSPACE = EGL_GL_COLORSPACE,
		VG_ALPHA_FORMAT = EGL_VG_ALPHA_FORMAT,
		VG_COLORSPACE = EGL_VG_COLORSPACE,
		CONFIG_ID = EGL_CONFIG_ID,
		HEIGHT = EGL_HEIGHT,
		HORIZONTAL_RESOLUTION = EGL_HORIZONTAL_RESOLUTION,
		LARGEST_PBUFFER = EGL_LARGEST_PBUFFER,
		MIPMAP_TEXTURE = EGL_MIPMAP_TEXTURE,
		MIPMAP_LEVEL = EGL_MIPMAP_LEVEL,
		MULTISAMPLE_RESOLVE = EGL_MULTISAMPLE_RESOLVE,
		PIXEL_ASPECT_RATIO = EGL_PIXEL_ASPECT_RATIO,
		RENDER_BUFFER = EGL_RENDER_BUFFER,
		SWAP_BEHAVIOR = EGL_SWAP_BEHAVIOR,
		TEXTURE_FORMAT = EGL_TEXTURE_FORMAT,
		TEXTURE_TARGET = EGL_TEXTURE_TARGET,
		VERTICAL_RESOLUTION = EGL_VERTICAL_RESOLUTION,
		WIDTH = EGL_WIDTH
	};
	template <QueryAttrib attribute>
	struct QueryValue;
	template <QueryAttrib attribute>
	using QueryValue_t = typename QueryValue<attribute>::type;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	static auto CreateWindow(
		const Display& display,
		const Config& config,
		NativeWindowType native_window,
		const std::unordered_map<Attribute, EGLint>& attrib_list = {}) -> Surface;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	constexpr auto GetHandle() const noexcept -> const EGLSurface&;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	static auto GetCurrent(const ReadDraw& readdraw) -> Surface;
	auto Attrib(
		EGLint attribute,
		EGLint value) -> EGLBoolean;
	template <QueryAttrib attribute>
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	auto Query() -> QueryValue_t<attribute>;
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
	explicit Surface(const EGLSurface& handle, const Display& display);
 private:
	EGLSurface handle{};
	std::reference_wrapper<std::add_const_t<Display>> display;
};
// clang-format off
template <> struct Surface::QueryValue<Surface::QueryAttrib::GL_COLORSPACE> { using type = gl::Colorspace; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::VG_ALPHA_FORMAT> { using type = vg::AlphaFormat; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::VG_COLORSPACE> { using type = vg::Colorspace; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::CONFIG_ID> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::HEIGHT> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::HORIZONTAL_RESOLUTION> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::LARGEST_PBUFFER> { using type = bool; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::MIPMAP_TEXTURE> { using type = bool; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::MIPMAP_LEVEL> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::MULTISAMPLE_RESOLVE> { using type = MultisampleResolve; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::PIXEL_ASPECT_RATIO> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::RENDER_BUFFER> { using type = RenderBuffer; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::SWAP_BEHAVIOR> { using type = SwapBehavior; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::TEXTURE_FORMAT> { using type = TextureFormat; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::TEXTURE_TARGET> { using type = TextureTarget; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::VERTICAL_RESOLUTION> { using type = EGLint; };
template <> struct Surface::QueryValue<Surface::QueryAttrib::WIDTH> { using type = EGLint; };
// clang-format on
} // namespace egl
namespace egl {
constexpr auto Surface::GetHandle() const noexcept -> const EGLSurface& {
	return this->handle;
}
template <Surface::QueryAttrib attrib>
auto Surface::Query() -> Surface::QueryValue_t<attrib> {
	EGLint value{};
	if (!EGLBooleanToBool(eglQuerySurface(this->display.get().GetHandle(), this->handle, std::to_underlying(attrib), &value))) {
		throw std::runtime_error{to_string(GetError())};
	}
	return static_cast<QueryValue_t<attrib>>(value);
}
} // namespace egl