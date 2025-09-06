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
#include <stdexcept>
#include <glad/egl.h>
export module egl:context;
import :display;
// import :config;
import :enums;
import :utils;
import :debug;
import :mapas;
import :misc;
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
	enum struct QueryAttrib : EGLenum {
		CONFIG_ID = EGL_CONFIG_ID,
		CONTEXT_CLIENT_TYPE = EGL_CONTEXT_CLIENT_TYPE,
		CONTEXT_CLIENT_VERSION = EGL_CONTEXT_CLIENT_VERSION,
		RENDER_BUFFER = EGL_RENDER_BUFFER,
	};
	template <QueryAttrib attrib>
	struct QueryValue;
	template <QueryAttrib attrib>
	using QueryValue_t = typename QueryValue<attrib>::type;
	Context(
		const Display& display,
		const Config& config,
		const std::optional<Context>& share_context = std::nullopt,
		const std::unordered_map<Attrib, EGLint>& attrib_list = {});
	~Context();
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	constexpr auto GetHandle() const noexcept -> const EGLContext&;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	static auto GetCurrent() -> Context;
	template <QueryAttrib attrib>
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	auto Query() -> QueryValue_t<attrib>;
	explicit Context(const EGLContext& context, const Display& display);
 private:
	EGLContext handle{};
	std::reference_wrapper<std::add_const_t<Display>> display;
};
// clang-format off
template <> struct Context::QueryValue<Context::QueryAttrib::CONFIG_ID> { using type = EGLint; };
template <> struct Context::QueryValue<Context::QueryAttrib::CONTEXT_CLIENT_TYPE> { using type = API; };
template <> struct Context::QueryValue<Context::QueryAttrib::CONTEXT_CLIENT_VERSION> { using type = EGLint; };
template <> struct Context::QueryValue<Context::QueryAttrib::RENDER_BUFFER> { using type = RenderBuffer; };
// clang-format on
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
template <Context::QueryAttrib attrib>
auto Context::Query() -> Context::QueryValue_t<attrib> {
	EGLint value{};
	if (!EGLBooleanToBool(eglQueryContext(this->display.get().GetHandle(), this->handle, std::to_underlying(attrib), &value))) {
		throw std::runtime_error{to_string(GetError())};
	}
	return static_cast<QueryValue_t<attrib>>(value);
}
} // namespace egl