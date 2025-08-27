/**
 * @file glad.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 27/08/2025
 *
 *
 */
module;
#include <optional>
#include <stdexcept>
#include <glad/egl.h>
module egl;
namespace glad {
#if GLAD_DEBUG
void SetEGLPreCallback(GLADprecallback cb) {
	gladSetEGLPreCallback(cb);
}
void SetEGLPostCallback(GLADpostcallback cb) {
	gladSetEGLPostCallback(cb);
}
void InstallEGLDebug() {
	gladInstallEGLDebug();
}
void UninstallEGLDebug() {
	gladUninstallEGLDebug();
}
#endif
void LoadEGLUserPtr(const egl::Display& display, GLADuserptrloadfunc load, void* userptr) {
	if (gladLoadEGLUserPtr(display.GetHandle(), load, userptr) == 0) {
		throw std::runtime_error{"error con el glad"};
	}
}
void LoadEGL(const egl::Display& display, GLADloadfunc load) {
	if (gladLoadEGL(display.GetHandle(), load) == 0) {
		throw std::runtime_error{"error con el glad"};
	}
}
void LoaderLoadEGL(const std::optional<egl::Display>& display) {
	if (gladLoaderLoadEGL(display ? display.value().GetHandle() : EGL_NO_DISPLAY) == 0) {
		throw std::runtime_error{"error con el glad"};
	}
}
void LoaderUnloadEGL() {}
} // namespace glad