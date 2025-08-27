/**
 * @file misc.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <utility>
#include <optional>
#include <stdexcept>
#include <glad/egl.h>
module egl;
import :enums;
import :mapas;
import :display;
namespace egl {
void BindAPI(const API& api) {
	if (!EGLBooleanToBool(eglBindAPI(std::to_underlying(api)))) {
		throw std::invalid_argument{to_string(GetError())};
	}
}
auto GetProcAddress(const char* procname) -> void(*)() {
	return eglGetProcAddress(procname);
}
void MakeCurrent(
	const Display& display,
	const Surface& draw,
	const Surface& read,
	const Context& context) {
	if (!EGLBooleanToBool(eglMakeCurrent(
				display.GetHandle(),
				draw.GetHandle(),
				read.GetHandle(),
				context.GetHandle()))) {
		throw std::runtime_error{to_string(GetError())};
	}
}
void ReleaseThread() {
	if (!EGLBooleanToBool(eglReleaseThread())) {
		throw std::runtime_error{to_string(GetError())};
	}
}
auto QueryAPI() -> APIq {
	return static_cast<APIq>(eglQueryAPI());
}
void WaitClient() {
	if (!EGLBooleanToBool(eglWaitClient())) {
		throw std::runtime_error{to_string(GetError())};
	}
}
} // namespace egl