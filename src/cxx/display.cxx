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
#include <unordered_map>
#include <any>
#include <vector>
#include <cstring>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
module egl;
namespace egl {
Display::Display(const EGLDisplay& handle) :
		handle{handle} {}
Display::~Display() {
	this->Terminate(); // no sé si es necesario
}
auto Display::GetCurrent() -> Display {
	return Display{eglGetCurrentDisplay()};
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
auto Display::ChooseConfig(const std::unordered_map<Attrib, EGLint> attrib_list) -> std::vector<Config> {
	std::vector<Config> resultado;
	std::vector<EGLint> list;
	list.reserve(attrib_list.size() * 2 + 1);
	for (const auto& [key, value] : attrib_list) {
		list.push_back(std::to_underlying(key));
		list.push_back(value);
	}
	list.push_back(EGL_NONE);
	EGLint num_config{};
	if (!EGLBooleanToBool(eglChooseConfig(this->handle, list.data(), nullptr, 0, &num_config))) {
		throw std::runtime_error{to_string(GetError())};
	}
	resultado.resize(num_config, Config{*this});
	if (!EGLBooleanToBool(eglChooseConfig(this->handle, list.data(), reinterpret_cast<EGLConfig*>(resultado.data()), resultado.size(), &num_config))) {
		throw std::runtime_error{to_string(GetError())};
	}
	return resultado;
}
void Display::Terminate() {
	if (!EGLBooleanToBool(eglTerminate(this->handle))) {
		throw std::runtime_error{to_string(GetError())};
	}
}
} // namespace egl