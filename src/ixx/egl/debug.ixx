/**
 * @file debug.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 23/08/2025
 *
 *
 */
module;
export module egl:debug;
import :enums;
export namespace egl {
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto GetError() -> Error;
} // namespace egl