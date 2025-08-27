/**
 * @file glad.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 27/08/2025
 *
 *
 */
module;
#include <optional>
#include <glad/egl.h>
export module egl:glad;
import :display;
export namespace glad {
#if GLAD_DEBUG
void SetEGLPreCallback(GLADprecallback cb);
void SetEGLPostCallback(GLADpostcallback cb);
void InstallEGLDebug();
void UninstallEGLDebug();
#endif
void LoadEGLUserPtr(const egl::Display& display, GLADuserptrloadfunc load, void* userptr);
void LoadEGL(const egl::Display& display, GLADloadfunc load);
void LoaderLoadEGL(const std::optional<egl::Display>& display = std::nullopt);
void LoaderUnloadEGL();
} // namespace glad