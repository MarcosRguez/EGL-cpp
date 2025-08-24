/**
 * @file debug.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 23/08/2025
 *
 *
 */
module;
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
module egl;
import :enums;
namespace egl {
auto GetError() -> Error {
	return static_cast<Error>(eglGetError());
}
} // namespace egl