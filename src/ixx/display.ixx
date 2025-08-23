/**
 * @file display.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <string_view>
#include <optional>
#include <vector>
#include <unordered_map>
#include <any>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:display;
import :enums;
// import :config;
export namespace egl {
class Config;
class Display {
 public:
	enum struct Attrib : EGLenum {
		ALPHA_MASK_SIZE = EGL_ALPHA_MASK_SIZE,
		ALPHA_SIZE = EGL_ALPHA_SIZE,
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
		MATCH_NATIVE_PIXMAP = EGL_MATCH_NATIVE_PIXMAP,
		NATIVE_RENDERABLE = EGL_NATIVE_RENDERABLE,
		MAX_SWAP_INTERVAL = EGL_MAX_SWAP_INTERVAL,
		MIN_SWAP_INTERVAL = EGL_MIN_SWAP_INTERVAL,
		RED_SIZE = EGL_RED_SIZE,
		SAMPLE_BUFFERS = EGL_SAMPLE_BUFFERS,
		SAMPLES = EGL_SAMPLES,
		STENCIL_SIZE = EGL_STENCIL_SIZE,
		RENDERABLE_TYPE = EGL_RENDERABLE_TYPE,
		SURFACE_TYPE = EGL_SURFACE_TYPE,
		TRANSPARENT_TYPE = EGL_TRANSPARENT_TYPE,
		TRANSPARENT_RED_VALUE = EGL_TRANSPARENT_RED_VALUE,
		TRANSPARENT_GREEN_VALUE = EGL_TRANSPARENT_GREEN_VALUE,
		TRANSPARENT_BLUE_VALUE = EGL_TRANSPARENT_BLUE_VALUE
	};
	~Display();
	static auto Get(const std::optional<NativeDisplayType>& native_display = std::nullopt) -> Display;
	static auto GetCurrent() -> Display;
	constexpr auto GetHandle() const noexcept -> const EGLDisplay&;
	auto Initialize() -> std::pair<EGLint, EGLint>;
	auto QueryString(const StringName&) -> std::string_view;
	void Terminate();
	auto ChooseConfig(const std::unordered_map<Attrib, EGLint> attrib_list) -> std::vector<Config>;
 private:
	EGLDisplay handle{};
	explicit Display(const EGLDisplay& handle);
};
} // namespace egl
namespace egl {
constexpr auto Display::GetHandle() const noexcept -> const EGLDisplay& {
	return this->handle;
}
} // namespace egl