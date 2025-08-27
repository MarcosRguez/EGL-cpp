cmake_minimum_required(VERSION 3.20)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION)
project(
	EGL++
	VERSION ${VERSION}
	LANGUAGES C CXX)
message(STATUS "Configurando '${PROJECT_NAME}' versión: ${VERSION}")
# Colorear las cositas
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
	set(BUILD_SHARED_LIBS OFF)
else()
	set(BUILD_SHARED_LIBS ON)
endif()

message(CHECK_START "Buscando ccache...")
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
	message(CHECK_PASS "ccache disponible")
	set(C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
	set(CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
	message(CHECK_FAIL "ccache no encontrado")
endif()

include(CheckIPOSupported)
message(CHECK_START "check_ipo_supported...")
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
	message(CHECK_PASS "IPO soportado")
else()
	message(CHECK_FAIL "IPO no soportado")
endif()

include(FindX11)
message(CHECK_START "Buscando X11...")
find_package(X11 REQUIRED)
if(X11_FOUND)
	message(CHECK_PASS "X11 encontrado")
else()
	message(CHECK_FAIL "X11 no encontrado")
endif()

include(FetchContent)

# glad
FetchContent_Declare(
	glad
	GIT_REPOSITORY git@github.com:Dav1dde/glad.git
	GIT_TAG v2.0.8)
FetchContent_MakeAvailable(glad)
add_subdirectory("${glad_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_BINARY_DIR}/gladsources")
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	# glad_add_library(glad DEBUG LOADER API egl=1.5 API gl:core=4.6)
	set(GLAD_DEBUG DEBUG)
else()
endif()
glad_add_library(glad ${GLAD_DEBUG} LOADER API egl=1.5 API gl:core=4.6)
set_target_properties(glad PROPERTIES
	C_STANDARD 23
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
)
if(ipo_supported AND NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
	set_target_properties(glad PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
	message(STATUS "Interprocedural optimization enabled for glad")
endif()
set(glad_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include")

set(LIB_NAME EGL++)

add_subdirectory("src")
add_subdirectory("tests")