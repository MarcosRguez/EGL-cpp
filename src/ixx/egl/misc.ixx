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
#include <glad/egl.h>
export module egl:misc;
import :enums;
// import :display;
// import :surface;
// import :config;
// import :sync;
// import :context;
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
auto GetProcAddress(const char* procname) -> void(*)();
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto QueryAPI() -> APIq;
void ReleaseThread();
void WaitClient();
EGLBoolean WaitGL();
EGLBoolean WaitNative(EGLint engine);
} // namespace egl