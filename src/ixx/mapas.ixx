/**
 * @file mapas.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <stdexcept>
#include <typeindex>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:mapas;
import :enums;
import :context;
namespace egl {
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto to_string(const Error& error) {
	switch (error) {
		case Error::SUCCESS: return "SUCCESS";
		case Error::NOT_INITIALIZED: return "NOT_INITIALIZED";
		case Error::BAD_ACCESS: return "BAD_ACCESS";
		case Error::BAD_ALLOC: return "BAD_ALLOC";
		case Error::BAD_ATTRIBUTE: return "BAD_ATTRIBUTE";
		case Error::BAD_CONTEXT: return "BAD_CONTEXT";
		case Error::BAD_CONFIG: return "BAD_CONFIG";
		case Error::BAD_CURRENT_SURFACE: return "BAD_CURRENT_SURFACE";
		case Error::BAD_DISPLAY: return "BAD_DISPLAY";
		case Error::BAD_SURFACE: return "BAD_SURFACE";
		case Error::BAD_MATCH: return "BAD_MATCH";
		case Error::BAD_PARAMETER: return "BAD_PARAMETER";
		case Error::BAD_NATIVE_PIXMAP: return "BAD_NATIVE_PIXMAP";
		case Error::BAD_NATIVE_WINDOW: return "BAD_NATIVE_WINDOW";
		case Error::CONTEXT_LOST: return "CONTEXT_LOST";
		default: throw std::invalid_argument{"🫗"};
	}
}
auto AttribToValue(const Attrib& attrib) -> std::type_index {
	switch (attrib) {
		case Attrib::MAJOR_VERSION: return typeid(EGLint);
		case Attrib::MINOR_VERSION: return typeid(EGLint);
		case Attrib::OPENGL_PROFILE_MASK: return typeid(EGLint);
		case Attrib::OPENGL_DEBUG: return typeid(EGLint);
		case Attrib::OPENGL_FORWARD_COMPATIBLE: return typeid(EGLint);
		case Attrib::OPENGL_ROBUST_ACCESS: return typeid(EGLint);
		case Attrib::OPENGL_RESET_NOTIFICATION_STRATEGY: return typeid(EGLint);
		default: throw std::invalid_argument{"🫗"};
	}
}
} // namespace egl