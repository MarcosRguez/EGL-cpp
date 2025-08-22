/**
 * @file display.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <optional>
#include <utility>
#include <stdexcept>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
module egl;
namespace egl {
Display::~Display() {
	this->Terminate(); // no sé si es necesario
}
auto Display::Initialize() -> std::pair<EGLint, EGLint> {
	EGLint major{};
	EGLint minor{};
	if (!EGLBooleanToBool(eglInitialize(this->handle, &major, &minor))) {
		throw std::runtime_error{to_string(GetError())};
	}
	return std::make_pair(major, minor);
}
auto Display::Get(const std::optional<NativeDisplayType>& native_display) -> Display {
	return Display{eglGetDisplay(native_display.value_or(EGL_DEFAULT_DISPLAY))};
}
} // namespace egl