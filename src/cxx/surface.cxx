/**
 * @file surface.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 23/08/2025
 *
 *
 */
module;
#include <unordered_map>
#include <any>
#include <vector>
#include <utility>
#include <stdexcept>
#include <glad/egl.h>
module egl;
namespace egl {
Surface::Surface(const EGLSurface& handle, const Display& display) :
		handle{handle},
		display{std::cref(display)} {}
auto Surface::CreateWindow(
	const Display& display,
	const Config& config,
	NativeWindowType native_window,
	const std::unordered_map<Attribute, EGLint>& attrib_list) -> Surface {
	std::vector<EGLint> list;
	list.reserve(attrib_list.size() * 2 + 1);
	for (const auto& [key, value] : attrib_list) {
		list.push_back(std::to_underlying(key));
		list.push_back(value);
	}
	list.push_back(EGL_NONE);
	Surface resultado{
		eglCreateWindowSurface(
			display.GetHandle(),
			config.GetHandle(),
			native_window,
			list.data()),
		display};
	if (resultado.GetHandle() == nullptr) {
		throw std::runtime_error{to_string(GetError())};
	}
	return resultado;
}
auto Surface::GetCurrent(const ReadDraw& readdraw) -> Surface {
	const auto resultado{eglGetCurrentSurface(std::to_underlying(readdraw))};
	if (resultado == EGL_NO_SURFACE) {
		throw std::runtime_error{"EGL_NO_SURFACE"};
	}
	return Surface{resultado, Display::GetCurrent()};
}
void Surface::SwapBuffers() {
	if (!EGLBooleanToBool(eglSwapBuffers(this->display.get().GetHandle(), this->handle))) {
		throw std::runtime_error{to_string(GetError())};
	}
}
} // namespace egl