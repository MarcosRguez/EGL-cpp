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
auto GetError() -> Error;
} // namespace egl