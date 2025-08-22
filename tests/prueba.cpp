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
#include <stdlib.h>
#include <unistd.h>
// #include <EGL/egl.h>
#include <GLES/gl.h>
#include <X11/Xlib.h>
import egl;
using namespace std::literals;
// static const EGLint attribute_list[] = {
// 	EGL_RED_SIZE, 1,
// 	EGL_GREEN_SIZE, 1,
// 	EGL_BLUE_SIZE, 1,
// 	EGL_NONE};
TEST_CASE("contexto") {
	egl::Config config;
	// egl::Context context;
	// egl::Surface surface;
	// NativeWindowType native_window;
	// EGLint num_config;
	/* get an EGL display connection */
	auto display{egl::Display::Get()};
	/* initialize the EGL display connection */
	// egl::Initialize(display, NULL, NULL);
	display.Initialize();
	/* get an appropriate EGL frame buffer configuration */
	// egl::ChooseConfig(display, attribute_list, &config, 1, &num_config);
	const auto configs{display.ChooseConfig(
		{{egl::Display::Attrib::RED_SIZE, std::make_any<int>(1)},
		 {egl::Display::Attrib::GREEN_SIZE, std::make_any<int>(1)},
		 {egl::Display::Attrib::BLUE_SIZE, std::make_any<int>(1)}})};
	/* create an EGL rendering context */
	// context = egl::CreateContext(display, config, EGL_NO_CONTEXT, NULL);
	const egl::Context context{display, config};
	/* create a native window */
	Display* MainDisplay = XOpenDisplay(0);
	Window RootWindow = XDefaultRootWindow(MainDisplay);
	auto native_window = XCreateSimpleWindow(
		MainDisplay,
		RootWindow,
		0,
		0,
		100,
		100,
		0,
		0,
		0);
	/* create an EGL window surface */
	// surface = egl::CreateWindowSurface(display, config, native_window, NULL);
	// const egl::Surface surface{display, config, native_window};
	const auto surface{egl::Surface::CreateWindow(display, configs.front(), native_window)};
	/* connect the context to the surface */
	egl::MakeCurrent(display, surface, surface, context);
	/* clear the color buffer */
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	egl::SwapBuffers(display, surface);
	sleep(10);
}