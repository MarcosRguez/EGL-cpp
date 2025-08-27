/**
 * @file context.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <optional>
#include <functional>
#include <span>
#include <utility>
#include <any>
#include <unordered_set>
#include <glad/egl.h>
export module egl:context;
// import :display;
// import :config;
import :utils;
export namespace egl {
class Display;
class Config;
class Surface;
class Context {
 public:
	enum struct Attrib : EGLenum {
		MAJOR_VERSION = EGL_CONTEXT_MAJOR_VERSION,
		MINOR_VERSION = EGL_CONTEXT_MINOR_VERSION,
		OPENGL_PROFILE_MASK = EGL_CONTEXT_OPENGL_PROFILE_MASK,
		OPENGL_DEBUG = EGL_CONTEXT_OPENGL_DEBUG,
		OPENGL_FORWARD_COMPATIBLE = EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,
		OPENGL_ROBUST_ACCESS = EGL_CONTEXT_OPENGL_ROBUST_ACCESS,
		OPENGL_RESET_NOTIFICATION_STRATEGY = EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY,
	};
	Context(
		const Display& display,
		const Config& config,
		const std::optional<Context>& share_context = std::nullopt,
		const std::unordered_map<Attrib, EGLint>& attrib_list = {});
	~Context();
	constexpr auto GetHandle() const noexcept -> const EGLContext&;
	static auto GetCurrent() -> Context;
	auto Query();
 private:
	EGLContext handle{};
	std::reference_wrapper<std::add_const_t<Display>> display;
};
void MakeCurrent(
	const Display& display,
	const Surface& draw,
	const Surface& read,
	const Context& context);
} // namespace egl
namespace egl {
constexpr auto Context::GetHandle() const noexcept -> const EGLContext& {
	return this->handle;
}
} // namespace egl