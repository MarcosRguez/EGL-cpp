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
#include <functional>
#include <stdexcept>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:config;
// import :display;
import :misc;
export namespace egl {
class Display;
class Config {
 public:
	enum struct Attrib : EGLenum {
		ALPHA_SIZE = EGL_ALPHA_SIZE,
		ALPHA_MASK_SIZE = EGL_ALPHA_MASK_SIZE,
		BIND_TO_TEXTURE_RGB = EGL_BIND_TO_TEXTURE_RGB,
		BIND_TO_TEXTURE_RGBA = EGL_BIND_TO_TEXTURE_RGBA,
		BLUE_SIZE = EGL_BLUE_SIZE,
		BUFFER_SIZE = EGL_BUFFER_SIZE,
		COLOR_BUFFER_TYPE = EGL_COLOR_BUFFER_TYPE,
		CONFIG_CAVEAT = EGL_CONFIG_CAVEAT,
		CONFIG_ID = EGL_CONFIG_ID,
		CONFORMANT = EGL_CONFORMANT,
		DEPTH_SIZE = EGL_DEPTH_SIZE,
		GREEN_SIZE = EGL_GREEN_SIZE,
		LEVEL = EGL_LEVEL,
		LUMINANCE_SIZE = EGL_LUMINANCE_SIZE,
		MAX_PBUFFER_WIDTH = EGL_MAX_PBUFFER_WIDTH,
		MAX_PBUFFER_HEIGHT = EGL_MAX_PBUFFER_HEIGHT,
		MAX_PBUFFER_PIXELS = EGL_MAX_PBUFFER_PIXELS,
		MAX_SWAP_INTERVAL = EGL_MAX_SWAP_INTERVAL,
		MIN_SWAP_INTERVAL = EGL_MIN_SWAP_INTERVAL,
		NATIVE_RENDERABLE = EGL_NATIVE_RENDERABLE,
		NATIVE_VISUAL_ID = EGL_NATIVE_VISUAL_ID,
		NATIVE_VISUAL_TYPE = EGL_NATIVE_VISUAL_TYPE,
		RED_SIZE = EGL_RED_SIZE,
		RENDERABLE_TYPE = EGL_RENDERABLE_TYPE,
		SAMPLE_BUFFERS = EGL_SAMPLE_BUFFERS,
		SAMPLES = EGL_SAMPLES,
		STENCIL_SIZE = EGL_STENCIL_SIZE,
		SURFACE_TYPE = EGL_SURFACE_TYPE,
		TRANSPARENT_TYPE = EGL_TRANSPARENT_TYPE,
		TRANSPARENT_RED_VALUE = EGL_TRANSPARENT_RED_VALUE,
		TRANSPARENT_GREEN_VALUE = EGL_TRANSPARENT_GREEN_VALUE,
		TRANSPARENT_BLUE_VALUE = EGL_TRANSPARENT_BLUE_VALUE
	};
	template <Attrib attrib>
	struct AttribValue;
	template <Attrib attrib>
	using AttribValue_t = typename AttribValue<attrib>::type;
	Config(const Display&);
	constexpr auto GetHandle() const noexcept -> const EGLConfig&;
	template <Attrib attribute>
	auto GetAttrib() const -> AttribValue_t<attribute>;
 private:
	EGLConfig handle{};
	std::reference_wrapper<std::add_const_t<Display>> display;
};
template <>
struct Config::AttribValue<Config::Attrib::ALPHA_SIZE> {
	using type = EGLint;
};
template <>
struct Config::AttribValue<Config::Attrib::CONFIG_ID> {
	using type = EGLint;
};
} // namespace egl
namespace egl {
constexpr auto Config::GetHandle() const noexcept -> const EGLConfig& {
	return this->handle;
}
template <Config::Attrib attribute>
auto Config::GetAttrib() const -> AttribValue_t<attribute> {
	AttribValue_t<attribute> value;
	if (!EGLBooleanToBool(eglGetConfigAttrib(this->display.get().GetHandle(), this->handle, attribute, reinterpret_cast<EGLint*>(&value)))) {
		throw std::runtime_error{to_string(GetError())};
	}
	return value;
}
} // namespace egl