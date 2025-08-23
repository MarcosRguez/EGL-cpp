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
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <X11/Xlib.h>
import egl;
using namespace std::literals;
auto createNativeWindow() -> NativeWindowType {
	static auto* MainDisplay{XOpenDisplay(0)};
	static auto RootWindow{XDefaultRootWindow(MainDisplay)};
	return XCreateSimpleWindow(
		MainDisplay,
		RootWindow,
		0,
		0,
		100,
		100,
		0,
		0,
		0);
}
TEST_CASE("eglIntro") {
	const EGLint attribute_list[] = {
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_NONE};
	EGLDisplay display;
	EGLConfig config;
	EGLContext context;
	EGLSurface surface;
	NativeWindowType native_window;
	EGLint num_config;
	/* get an EGL display connection */
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	/* initialize the EGL display connection */
	eglInitialize(display, NULL, NULL);
	/* get an appropriate EGL frame buffer configuration */
	eglChooseConfig(display, attribute_list, &config, 1, &num_config);
	// inspeccionar config
	{
		EGLint value{};
		eglGetConfigAttrib(display, config, EGL_ALPHA_SIZE, &value);
		std::println(std::cout, "{}: {}", "EGL_ALPHA_SIZE", value);
		eglGetConfigAttrib(display, config, EGL_CONFIG_ID, &value);
		std::println(std::cout, "{}: {}", "EGL_CONFIG_ID", value);
	}
	/* create an EGL rendering context */
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
	/* create a native window */
	native_window = createNativeWindow();
	/* create an EGL window surface */
	surface = eglCreateWindowSurface(display, config, native_window, NULL);
	/* connect the context to the surface */
	eglMakeCurrent(display, surface, surface, context);
	/* clear the color buffer */
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	eglSwapBuffers(display, surface);
	// sleep(10);
}
TEST_CASE("contexto") {
	auto display{egl::Display::Get()};
	/* initialize the EGL display connection */
	display.Initialize();
	/* get an appropriate EGL frame buffer configuration */
	const auto configs{display.ChooseConfig(
		{{egl::Display::Attrib::RED_SIZE, 1},
		 {egl::Display::Attrib::GREEN_SIZE, 1},
		 {egl::Display::Attrib::BLUE_SIZE, 1}})};
	for (const auto& config : configs) {
		std::println(std::cout, "{}: {}", "EGL_CONFIG_ID", config.GetAttrib<egl::Config::Attrib::CONFIG_ID>());
	}
	/* create an EGL rendering context */
	const egl::Context context{display, configs.front()};
	/* create a native window */
	auto native_window = createNativeWindow();
	/* create an EGL window surface */
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