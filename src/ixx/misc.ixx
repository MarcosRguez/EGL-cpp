/**
 * @file misc.ixx
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
#include <chrono>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:misc;
import :enums;
import :display;
import :surface;
import :config;
import :sync;
import :context;
namespace egl {
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto BoolToEGLBoolean(const bool& value) noexcept -> EGLBoolean {
	return value ? EGL_TRUE : EGL_FALSE;
}
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto EGLBooleanToBool(const EGLBoolean& value) noexcept -> bool {
	return value == EGL_TRUE;
}
} // namespace egl
export namespace egl {
void BindAPI(const API& api);
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto BindTexImage(
	const Display& display,
	const Surface& surface,
	EGLint buffer) -> bool;
// auto ChooseConfig(
// 	const Display& display,
// 	const std::unordered_map<EGLint, EGLint> attrib_list) -> std::vector<Config>;
auto ClientWaitSync(
	const Display& display,
	const Sync& sync,
	EGLint flags,
	const std::chrono::nanoseconds& timeout) -> EGLint;
auto CopyBuffers(
	const Display& display,
	const Surface& surface,
	NativePixmapType native_pixmap) -> bool;
auto GetConfigAttrib(
	const Display& display,
	const Config& config,
	EGLint attribute,
	EGLint* value) -> bool;
auto GetConfigs(
	const Display& display,
	Config* configs,
	EGLint config_size,
	EGLint* num_config) -> bool;
auto GetCurrentContext() -> Context;
auto GetCurrentDisplay() -> Display;
auto GetCurrentSurface(EGLint readdraw) -> Surface;
// auto GetDisplay(const std::optional<NativeDisplayType>& native_display = std::nullopt) -> Display;
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto GetError() -> Error;
auto GetPlatformDisplay(
	EGLenum platform,
	void* native_display,
	const EGLAttrib* attrib_list) -> Display;
auto GetProcAddress(const char* procname) -> void*;
auto GetSyncAttrib(
	const Display& display,
	EGLSync sync,
	EGLint attribute,
	EGLAttrib* value) -> bool;
// auto Initialize(
// 	const Display& display,
// 	EGLint* major,
// 	EGLint* minor) -> bool;
void MakeCurrent(
	const Display& display,
	const Surface& draw,
	const Surface& read,
	const Context& context);
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto QueryAPI() -> APIq;
// auto QueryContext(
// 	const Display& display,
// 	const Context& context,
// 	EGLint attribute,
// 	EGLint* value) -> bool;
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto QueryString(Display display, EGLint name) -> std::string_view;
// auto QuerySurface(
// 	const Display& display,
// 	const Surface& surface,
// 	EGLint attribute,
// 	EGLint* value) -> EGLBoolean;
auto ReleaseTexImage(
	const Display& display,
	const Surface& surface,
	EGLint buffer) -> EGLBoolean;
void ReleaseThread();
auto SurfaceAttrib(
	const Display& display,
	const Surface& surface,
	EGLint attribute,
	EGLint value) -> EGLBoolean;
auto SwapBuffers(
	const Display& display,
	const Surface& surface) -> EGLBoolean;
auto SwapInterval(
	const Display& display,
	EGLint interval) -> EGLBoolean;
// auto Terminate(Display display) -> EGLBoolean;
void WaitClient();
EGLBoolean WaitGL();
EGLBoolean WaitNative(EGLint engine);
EGLBoolean WaitSync(
	const Display& display,
	const Sync& sync,
	EGLint flags);
} // namespace egl