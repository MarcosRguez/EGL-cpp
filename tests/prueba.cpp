/**
 * @file test.cpp
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 25/05/2025
 *
 *
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.hpp>
#include <any>
#include <iostream>
#include <print>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <EGL/egl.h>
#include <glad/egl.h>
#include <glad/gl.h>
import egl;
using namespace std::literals;
auto* pantalla{XOpenDisplay(nullptr)};
auto rootWindow{XDefaultRootWindow(pantalla)};
// TEST_CASE("eglIntro") {
// 	const EGLint attribute_list[] = {
// 		EGL_RED_SIZE, 1,
// 		EGL_GREEN_SIZE, 1,
// 		EGL_BLUE_SIZE, 1,
// 		EGL_NONE};
// 	EGLDisplay display;
// 	EGLConfig config;
// 	EGLContext context;
// 	EGLSurface surface;
// 	NativeWindowType native_window;
// 	EGLint num_config;
// 	/* get an EGL display connection */
// 	display = eglGetDisplay(pantalla);
// 	/* initialize the EGL display connection */
// 	eglInitialize(display, NULL, NULL);
// 	/* get an appropriate EGL frame buffer configuration */
// 	eglChooseConfig(display, attribute_list, &config, 1, &num_config);
// 	// inspeccionar config
// 	{
// 		EGLint value{};
// 		eglGetConfigAttrib(display, config, EGL_ALPHA_SIZE, &value);
// 		std::println(std::cout, "{}: {}", "EGL_ALPHA_SIZE", value);
// 		eglGetConfigAttrib(display, config, EGL_CONFIG_ID, &value);
// 		std::println(std::cout, "{}: {}", "EGL_CONFIG_ID", value);
// 	}
// 	/* create an EGL rendering context */
// 	context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
// 	/* create a native window */
// 	native_window = XCreateSimpleWindow(
// 		pantalla,
// 		RootWindow,
// 		0,
// 		0,
// 		100,
// 		100,
// 		0,
// 		0,
// 		0);
// 	/* create an EGL window surface */
// 	surface = eglCreateWindowSurface(display, config, native_window, NULL);
// 	/* connect the context to the surface */
// 	eglMakeCurrent(display, surface, surface, context);
// 	/* clear the color buffer */
// 	glClearColor(1.0, 1.0, 0.0, 1.0);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glFlush();
// 	eglSwapBuffers(display, surface);
// 	// sleep(10);
// 	XDestroyWindow(pantalla, native_window);
// }
TEST_CASE("contexto") {
	std::println(std::cout, "EGL++");
	// const auto disp{eglGetDisplay(EGL_DEFAULT_DISPLAY)};
	gladLoaderLoadEGL(EGL_NO_DISPLAY);
	auto display{egl::Display::Get(std::make_optional(pantalla))};
	/* initialize the EGL display connection */
	display.Initialize();
	/* get an appropriate EGL frame buffer configuration */
	const auto configs{display.ChooseConfig(
		{{egl::Display::Attrib::RED_SIZE, 1},
		 {egl::Display::Attrib::GREEN_SIZE, 1},
		 {egl::Display::Attrib::BLUE_SIZE, 1},
		 {egl::Display::Attrib::DEPTH_SIZE, 24},
		 {egl::Display::Attrib::STENCIL_SIZE, 0},
		 {egl::Display::Attrib::SAMPLES, 0},
		 {egl::Display::Attrib::RENDERABLE_TYPE, EGL_OPENGL_ES_BIT},
		 {egl::Display::Attrib::SURFACE_TYPE, EGL_WINDOW_BIT}})};
	// const auto configs{display.ChooseConfig()};
	// for (const auto& config : configs) {
	// 	std::println(std::cout, "-------------------");
	// 	std::println(std::cout, "{}: {}", "ALPHA_SIZE", config.GetAttrib<egl::Config::Attrib::ALPHA_SIZE>());
	// 	std::println(std::cout, "{}: {}", "ALPHA_MASK_SIZE", config.GetAttrib<egl::Config::Attrib::ALPHA_MASK_SIZE>());
	// 	std::println(std::cout, "{}: {}", "BIND_TO_TEXTURE_RGB", config.GetAttrib<egl::Config::Attrib::ALPHA_MASK_SIZE>());
	// 	std::println(std::cout, "{}: {}", "BIND_TO_TEXTURE_RGBA", config.GetAttrib<egl::Config::Attrib::BIND_TO_TEXTURE_RGBA>());
	// 	std::println(std::cout, "{}: {}", "BLUE_SIZE", config.GetAttrib<egl::Config::Attrib::BLUE_SIZE>());
	// 	std::println(std::cout, "{}: {}", "BUFFER_SIZE", config.GetAttrib<egl::Config::Attrib::BUFFER_SIZE>());
	// 	std::println(std::cout, "{}: {}", "CONFIG_CAVEAT", config.GetAttrib<egl::Config::Attrib::CONFIG_CAVEAT>());
	// 	std::println(std::cout, "{}: {}", "CONFIG_ID", config.GetAttrib<egl::Config::Attrib::CONFIG_ID>());
	// 	std::println(std::cout, "{}: {}", "CONFORMANT", config.GetAttrib<egl::Config::Attrib::CONFORMANT>());
	// 	std::println(std::cout, "{}: {}", "DEPTH_SIZE", config.GetAttrib<egl::Config::Attrib::DEPTH_SIZE>());
	// 	std::println(std::cout, "{}: {}", "GREEN_SIZE", config.GetAttrib<egl::Config::Attrib::GREEN_SIZE>());
	// 	std::println(std::cout, "{}: {}", "LEVEL", config.GetAttrib<egl::Config::Attrib::LEVEL>());
	// 	std::println(std::cout, "{}: {}", "LUMINANCE_SIZE", config.GetAttrib<egl::Config::Attrib::LUMINANCE_SIZE>());
	// 	std::println(std::cout, "{}: {}", "MAX_PBUFFER_WIDTH", config.GetAttrib<egl::Config::Attrib::MAX_PBUFFER_WIDTH>());
	// 	std::println(std::cout, "{}: {}", "MAX_PBUFFER_HEIGHT", config.GetAttrib<egl::Config::Attrib::MAX_PBUFFER_HEIGHT>());
	// 	std::println(std::cout, "{}: {}", "MAX_PBUFFER_PIXELS", config.GetAttrib<egl::Config::Attrib::MAX_PBUFFER_PIXELS>());
	// 	std::println(std::cout, "{}: {}", "MAX_SWAP_INTERVAL", config.GetAttrib<egl::Config::Attrib::MAX_SWAP_INTERVAL>());
	// 	std::println(std::cout, "{}: {}", "MIN_SWAP_INTERVAL", config.GetAttrib<egl::Config::Attrib::MIN_SWAP_INTERVAL>());
	// 	std::println(std::cout, "{}: {}", "NATIVE_RENDERABLE", config.GetAttrib<egl::Config::Attrib::NATIVE_RENDERABLE>());
	// 	std::println(std::cout, "{}: {}", "NATIVE_VISUAL_ID", config.GetAttrib<egl::Config::Attrib::NATIVE_VISUAL_ID>());
	// 	std::println(std::cout, "{}: {}", "NATIVE_VISUAL_TYPE", config.GetAttrib<egl::Config::Attrib::NATIVE_VISUAL_TYPE>());
	// 	std::println(std::cout, "{}: {}", "RED_SIZE", config.GetAttrib<egl::Config::Attrib::RED_SIZE>());
	// 	std::println(std::cout, "{}: {}", "RENDERABLE_TYPE", config.GetAttrib<egl::Config::Attrib::RENDERABLE_TYPE>());
	// 	std::println(std::cout, "{}: {}", "SAMPLE_BUFFERS", config.GetAttrib<egl::Config::Attrib::SAMPLE_BUFFERS>());
	// 	std::println(std::cout, "{}: {}", "SAMPLES", config.GetAttrib<egl::Config::Attrib::SAMPLES>());
	// 	std::println(std::cout, "{}: {}", "STENCIL_SIZE", config.GetAttrib<egl::Config::Attrib::STENCIL_SIZE>());
	// 	std::println(std::cout, "{}: {}", "SURFACE_TYPE", config.GetAttrib<egl::Config::Attrib::SURFACE_TYPE>());
	// 	std::println(std::cout, "{}: {}", "TRANSPARENT_TYPE", config.GetAttrib<egl::Config::Attrib::TRANSPARENT_TYPE>());
	// 	std::println(std::cout, "{}: {}", "TRANSPARENT_RED_VALUE", config.GetAttrib<egl::Config::Attrib::TRANSPARENT_RED_VALUE>());
	// 	std::println(std::cout, "{}: {}", "TRANSPARENT_GREEN_VALUE", config.GetAttrib<egl::Config::Attrib::TRANSPARENT_GREEN_VALUE>());
	// 	std::println(std::cout, "{}: {}", "TRANSPARENT_BLUE_VALUE", config.GetAttrib<egl::Config::Attrib::TRANSPARENT_BLUE_VALUE>());
	// }
	/* create an EGL rendering context */
	const egl::Context context{display, configs.front()};
	/* create a native window */
	auto native_window{XCreateWindow(
		pantalla,
		rootWindow,
		0,
		0,
		100,
		100,
		0,
		0,
		0,
		nullptr,
		0,
		nullptr)};
	/* create an EGL window surface */
	bool lanza{false};
	for (const auto& i : configs) {
		lanza = false;
		try {
			auto surface{egl::Surface::CreateWindow(display, i, native_window)};
		} catch (...) {
			lanza = true;
			// std::cout << i.GetAttrib<egl::Config::Attrib::CONFIG_ID>() << " lanza excepción" << '\n';
		}
		if (!lanza) {
			std::cout << i.GetAttrib<egl::Config::Attrib::CONFIG_ID>() << " no lanza excepción!!!" << '\n';
		}
	}
	auto surface{egl::Surface::CreateWindow(display, configs.front(), native_window)};
	/* connect the context to the surface */
	egl::MakeCurrent(display, surface, surface, context);
	/* clear the color buffer */
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	surface.SwapBuffers();
	// sleep(10);
}