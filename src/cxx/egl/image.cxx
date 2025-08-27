/**
 * @file image.cxx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 21/08/2025
 *
 *
 */
module;
#include <iostream>
#include <print>
#include <glad/egl.h>
module egl;
namespace egl {
Image::Image() {}
Image::~Image() {
	// if (!EGLBooleanToBool(eglDestroyImage(, this->handle))) {
	// 	std::println(std::cerr, "mal");
	// }
}
} // namespace egl