/**
 * @file utils.ixx
 * @author MarcosRguez (alu0101470368@ull.edu.es)
 * @brief
 * @version 0.1
 * @date 02/05/2024
 *
 *
 */
module;
#include <filesystem>
#include <array>
#include <vector>
#include <deque>
#include <fstream>
#include <forward_list>
#include <list>
#include <map>
#include <unordered_map>
#include <variant>
#include <type_traits>
#include <ranges>
#include <algorithm>
module egl:utils;
// export {
template <typename T, template <typename...> typename D>
struct is_specialization : std::false_type {};
template <template <typename...> typename T, typename... D>
struct is_specialization<T<D...>, T> : std::true_type {};
template <typename T, template <typename...> typename D>
inline constexpr auto is_specialization_v{is_specialization<T, D>::value};
template <typename E>
requires std::is_enum_v<E>
struct enable_enum_bitwise_ops : std::false_type {};
template <typename E>
constexpr auto enable_enum_bitwise_ops_v{enable_enum_bitwise_ops<E>::value};
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator&(const E& lhs, const E& rhs) -> E {
	using U = std::underlying_type_t<E>;
	return static_cast<E>(static_cast<U>(lhs) & static_cast<U>(rhs));
}
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator|(const E& lhs, const E& rhs) -> E {
	using U = std::underlying_type_t<E>;
	return static_cast<E>(static_cast<U>(lhs) | static_cast<U>(rhs));
}
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator^(const E& lhs, const E& rhs) -> E {
	using U = std::underlying_type_t<E>;
	return static_cast<E>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
}
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator&=(const E& lhs, const E& rhs) -> E {
	return lhs = lhs & rhs;
}
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator|=(const E& lhs, const E& rhs) -> E {
	return lhs = lhs | rhs;
}
template <typename E>
requires std::is_enum_v<E> && enable_enum_bitwise_ops_v<E>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto operator^=(const E& lhs, const E& rhs) -> E {
	return lhs = lhs ^ rhs;
}
/**
 * @brief Carga un fichero
 * @tparam T std::string o std::vector
 * @param ruta ruta al fichero
 * @return Datos del fichero en la estructura del parámetro de plantilla
 */
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto CargarFichero(
	const
#if __cpp_lib_filesystem >= 201703L
	std::filesystem::path
#else
	std::string
#endif
		& ruta) -> T {
#if __cpp_lib_logical_traits >= 201510L
	static_assert(std::disjunction_v<std::is_same<T, std::string>, is_specialization<T, std::vector>>);
#endif
	T resultado;
	std::fstream file{ruta};
	if (!file.is_open()) { throw std::runtime_error{"Fichero no encontrado"}; }
	auto fsize{file.tellg()};
	file.seekg(0, std::fstream::end);
	fsize = file.tellg() - fsize;
	resultado.resize(fsize);
	file.seekg(std::fstream::beg);
	file.read(
		reinterpret_cast<char*>(
#if __cplusplus >= 201703L
			resultado.data()
#else
			const_cast<char*>(resultado.data())
#endif
				),
		fsize);
	return resultado;
}
template <typename T, std::size_t N>
constexpr auto contains(const std::array<T, N>& contenedor, const T& valor) noexcept -> bool {
	return
#if __cpp_lib_ranges >= 201911L
		std::ranges::find(contenedor, valor)
#else
		std::find(contenedor.cbegin(), contenedor.cend(), valor)
#endif
		!= contenedor.cend();
}
template <typename T>
constexpr auto contains(const std::vector<T>& contenedor, const T& valor) noexcept -> bool {
	return
#if __cpp_lib_ranges >= 201911L
		std::ranges::find(contenedor, valor)
#else
		std::find(contenedor.cbegin(), contenedor.cend(), valor)
#endif
		!= contenedor.cend();
}
template <typename T>
constexpr auto contains(const std::deque<T>& contenedor, const T& valor) noexcept -> bool {
	return
#if __cpp_lib_ranges >= 201911L
		std::ranges::find(contenedor, valor)
#else
		std::find(contenedor.cbegin(), contenedor.cend(), valor)
#endif
		!= contenedor.cend();
}
template <typename T>
constexpr auto contains(const std::forward_list<T>& contenedor, const T& valor) noexcept -> bool {
	return
#if __cpp_lib_ranges >= 201911L
		std::ranges::find(contenedor, valor)
#else
		std::find(contenedor.cbegin(), contenedor.cend(), valor)
#endif
		!= contenedor.cend();
}
template <typename T>
constexpr auto contains(const std::list<T>& contenedor, const T& valor) noexcept -> bool {
	return
#if __cpp_lib_ranges >= 201911L
		std::ranges::find(contenedor, valor)
#else
		std::find(contenedor.cbegin(), contenedor.cend(), valor)
#endif
		!= contenedor.cend();
}
template <typename T, std::size_t N>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto size_bytes(const std::array<T, N>&) noexcept -> std::size_t;
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto size_bytes(const std::vector<T>& contenedor) noexcept -> std::size_t {
	return contenedor.size() * sizeof(T);
}
#if __cpp_lib_inplace_vector >= 202406L
template <typename T>
	#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
	#endif
constexpr auto size_bytes(const std::inplace_vector<T>&) noexcept -> std::size_t;
#endif
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto size_bytes(const std::deque<T>&) noexcept -> std::size_t;
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto size_bytes(const std::forward_list<T>&) noexcept -> std::size_t;
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto size_bytes(const std::list<T>&) noexcept -> std::size_t;
#if __cplusplus >= 202002L
template <typename L, typename R>
	#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
	#endif
constexpr auto operator<=>(const std::reference_wrapper<L>& lhs, const std::reference_wrapper<R>& rhs) {
	return lhs.get() <=> rhs.get();
}
template <typename L, typename R>
	#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
	#endif
constexpr auto operator<=>(const std::reference_wrapper<const L>& lhs, const std::reference_wrapper<const R>& rhs) {
	return lhs.get() <=> rhs.get();
}
template <typename L, typename R>
	#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
	#endif
constexpr auto operator==(const std::reference_wrapper<L>& lhs, const std::reference_wrapper<R>& rhs) -> bool {
	return lhs.get() == rhs.get();
}
template <typename L, typename R>
	#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
	#endif
constexpr auto operator!=(const std::reference_wrapper<L>& lhs, const std::reference_wrapper<R>& rhs) -> bool {
	return lhs.get() != rhs.get();
}
#endif
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto unmove(T&& t) noexcept -> T& {
	return static_cast<T&>(t);
}
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
constexpr auto EsPotenciaDeDos(const int& n) -> bool {
	return n != 0 && (n & (n - 1)) == 0;
}
template <typename K, typename V>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto keys(const std::map<K, V>& map) -> std::vector<K> {
	std::vector<K> resultado;
	for (const auto& [key, _] : map) {
		resultado.push_back(key);
	}
	return resultado;
}
template <typename K, typename V>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto keys(const std::unordered_map<K, V>& map) -> std::vector<K> {
	std::vector<K> resultado;
	for (const auto& [key, _] : map) {
		resultado.push_back(key);
	}
	return resultado;
}
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto make_span(const std::span<T>& ilist) -> std::span<std::add_const_t<T>> {
	return {ilist.begin(), ilist.size()};
}
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto make_span(const std::initializer_list<T>& ilist) -> std::span<std::add_const_t<T>> {
	return {ilist.begin(), ilist.size()};
}
template <typename T, std::size_t N>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto make_span(const std::array<T, N>& ilist) -> std::span<std::add_const_t<T>, N> {
	return {ilist};
}
template <typename T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto make_span(const std::vector<T>& ilist) -> std::span<std::add_const_t<T>> {
	return {ilist.begin(), ilist.size()};
}
template <typename... T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto VecToVar(const std::vector<std::variant<T...>>& vec) -> std::variant<std::vector<T>...> {
	std::variant<std::vector<T>...> resultado;
	for (const auto& i : vec) {
		i.visit([&](const auto& value) {
			std::get<std::vector<std::remove_cvref_t<decltype(value)>>>(resultado).push_back(value);
		});
	}
	return resultado;
}
template <typename... T>
#if __has_cpp_attribute(nodiscard)
[[nodiscard]]
#endif
auto VarToVec(const std::variant<std::vector<T>...>& var) -> std::vector<std::variant<T...>> {
	std::vector<std::variant<T...>> resultado;
	var.visit([&](const auto& vec) {
		for (const auto& i : vec) {
			resultado.push_back(i);
		}
	});
	return resultado;
}
// }