/**
 * @file sync.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <chrono>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <EGL/eglmesaext.h>
#include <EGL/eglplatform.h>
export module egl:sync;
export namespace egl {
class Sync {
 public:
	auto ClientWait(
		EGLint flags,
		const std::chrono::nanoseconds& timeout) -> EGLint;
	auto GetAttrib(
		EGLint attribute,
		EGLAttrib* value) -> bool;
	EGLBoolean Wait(EGLint flags);
 private:
	EGLSync handle{};
};
} // namespace egl