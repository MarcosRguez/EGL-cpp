/**
 * @file image.ixx
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
export module egl:image;
export namespace egl {
class Image {
 public:
	Image();
	~Image();
 private:
	EGLImage handle{};
};
} // namespace egl