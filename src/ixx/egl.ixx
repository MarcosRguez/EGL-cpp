/**
 * @file egl.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl;
export import :utils;
export import :misc;
export import :enums;
export import :mapas;
export import :context;
export import :image;
export import :display;
export import :config;
export import :surface;
export import :sync;