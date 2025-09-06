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
#include <glad/egl.h>
export module egl:sync;
export namespace egl {
class Sync {
 public:
	auto ClientWait(
		EGLint flags,
		const std::chrono::nanoseconds& timeout) -> EGLint;
#if __has_cpp_attribute(nodiscard)
	[[nodiscard]]
#endif
	auto GetAttrib(
		EGLint attribute,
		EGLAttrib* value) -> bool;
	EGLBoolean Wait(EGLint flags);
 private:
	EGLSync handle{};
};
} // namespace egl