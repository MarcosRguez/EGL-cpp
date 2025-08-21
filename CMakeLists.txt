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

include(FetchContent)
include(CheckIPOSupported)

message(CHECK_START "check_ipo_supported...")
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
	message(CHECK_PASS "IPO soportado")
else()
	message(CHECK_FAIL "IPO no soportado")
endif()

set(LIB_NAME EGL++)

add_subdirectory("src")
add_subdirectory("tests")