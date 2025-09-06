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
#include <glad/egl.h>
module egl;
import :config;
namespace egl {
Display::Display(const EGLDisplay& handle) :
		handle{handle} {}
Display::~Display() {
	this->Terminate(); // no sé si es necesario
}
auto Display::GetConfigs() -> std::vector<Config> {
	std::vector<Config> resultado;
	std::vector<EGLConfig> cosa;
	EGLint num_config{};
	if (!EGLBooleanToBool(eglGetConfigs(this->handle, nullptr, 0, &num_config))) {
		throw std::runtime_error{to_string(GetError())};
	}
	cosa.resize(num_config);
	if (!EGLBooleanToBool(eglGetConfigs(this->handle, cosa.data(), cosa.size(), &num_config))) {
		throw std::runtime_error{to_string(GetError())};
	}
	for (const auto& i : cosa) {
		resultado.push_back(Config{i, *this});
	}
	return resultado;
}
auto Display::GetCurrent() -> Display {
	const auto handle{eglGetCurrentDisplay()};
	if (handle == EGL_NO_DISPLAY) {
		throw std::runtime_error{"EGL_NO_DISPLAY"};
	}
	return Display{handle};
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
	const auto resultado{eglGetDisplay(native_display.value_or(EGL_DEFAULT_DISPLAY))};
	if (resultado == EGL_NO_DISPLAY) {
		throw std::runtime_error{"EGL_NO_DISPLAY"};
	}
	return Display{resultado};
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
	resultado.reserve(num_config);
	std::vector<EGLConfig> cosa;
	cosa.resize(num_config);
	if (!EGLBooleanToBool(eglChooseConfig(this->handle, list.data(), cosa.data(), cosa.size(), &num_config))) {
		throw std::runtime_error{to_string(GetError())};
	}
	for (const auto& id : cosa) {
		resultado.push_back(Config{id, *this});
	}
	return resultado;
}
void Display::SwapInterval(const EGLint& interval) {
	if (!EGLBooleanToBool(eglSwapInterval(this->handle, interval))) {
		throw std::runtime_error{to_string(GetError())};
	}
}
void Display::Terminate() {
	if (!EGLBooleanToBool(eglTerminate(this->handle))) {
		throw std::runtime_error{to_string(GetError())};
	}
}
auto Display::QueryString(const StringName& name) const -> std::string_view {
	return std::string_view{eglQueryString(this->handle, std::to_underlying(name))};
}
} // namespace egl