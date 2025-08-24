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
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
module egl;
import :misc;
namespace egl {
Context::Context(
	const Display& display,
	const Config& config,
	const std::optional<Context>& share_context,
	const std::unordered_map<Attrib, EGLint>& attrib_list) :
		handle{eglCreateContext(
			display.GetHandle(),
			config.GetHandle(),
			share_context ? share_context.value().GetHandle() : EGL_NO_CONTEXT,
			[&]() {
				std::vector<EGLint> resultado;
				resultado.reserve(attrib_list.size() * 2uz);
				for (const auto& [key, value] : attrib_list) {
					resultado.push_back(std::to_underlying(key));
					resultado.push_back(value);
				}
				return resultado.data();
			}())},
			display{std::cref(display)} {}
Context::~Context() {
	if (!EGLBooleanToBool(eglDestroyContext(this->display.get().GetHandle(), this->handle))) {
		std::println(std::cerr, "Error al destruir el contexto: {}", to_string(GetError()));
	}
}
} // namespace egl