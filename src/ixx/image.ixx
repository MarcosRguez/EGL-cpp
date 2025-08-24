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
#include <glad/egl.h>
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