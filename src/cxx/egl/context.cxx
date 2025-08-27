/**
 * @file context.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <iostream>
#include <print>
#include <any>
#include <unordered_map>
#include <utility>
#include <bit>
#include <cstring>
#include <glad/egl.h>
module egl;
import :misc;
namespace egl {
Context::Context(
	const Display& display,
	const Config& config,
	const std::optional<Context>& share_context,
	const std::unordered_map<Attrib, EGLint>& attrib_list) :
		display{std::cref(display)} {
	std::vector<EGLint> attribs;
	attribs.reserve(attrib_list.size() * 2uz + 1);
	for (const auto& [key, value] : attrib_list) {
		attribs.push_back(std::to_underlying(key));
		attribs.push_back(value);
	}
	attribs.push_back(EGL_NONE);
	this->handle = eglCreateContext(
		display.GetHandle(),
		config.GetHandle(),
		share_context ? share_context.value().GetHandle() : EGL_NO_CONTEXT, attribs.data());
}
Context::~Context() {
	if (!EGLBooleanToBool(eglDestroyContext(this->display.get().GetHandle(), this->handle))) {
		std::println(std::cerr, "Error al destruir el contexto: {}", to_string(GetError()));
	}
}
} // namespace egl