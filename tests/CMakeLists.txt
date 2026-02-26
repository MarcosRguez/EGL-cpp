# Directorio de dependencias 'header-only'
set(EXTERNAL "${CMAKE_CURRENT_BINARY_DIR}/external")
file(MAKE_DIRECTORY "${EXTERNAL}")

# doctest
file(MAKE_DIRECTORY "${EXTERNAL}/doctest")
file(DOWNLOAD
		"https://github.com/doctest/doctest/releases/download/v2.4.11/doctest.h"
		"${EXTERNAL}/doctest/doctest.hpp")

set(TEST_OPTION "${PROJECT_NAME}_BUILD_TESTS")
option(${TEST_OPTION} "Compilar los tests")

if(${TEST_OPTION})
	enable_testing()
	glad_add_library(glad-gl ${GLAD_DEBUG} LOADER API gl:core=4.6)
	set_target_properties(glad-egl PROPERTIES
		C_STANDARD 23
		C_STANDARD_REQUIRED ON
		C_EXTENSIONS OFF
	)
	if(ipo_supported AND NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
		set_target_properties(glad-gl PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
		message(STATUS "Interprocedural optimization enabled for glad-gl")
	endif()
	file(GLOB TESTS CONFIGURE_DEPENDS "*.cpp")
	foreach(TEST ${TESTS})
		get_filename_component(TEST_NAME ${TEST} NAME_WE)
		add_executable("${PROJECT_NAME}_${TEST_NAME}" ${TEST})
		set_target_properties("${PROJECT_NAME}_${TEST_NAME}" PROPERTIES
			CXX_STANDARD 26
			CXX_STANDARD_REQUIRED ON
			CXX_EXTENSIONS OFF
			CXX_SCAN_FOR_MODULES ON
		)
		if(ipo_supported AND NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
			set_target_properties("${PROJECT_NAME}_${TEST_NAME}" PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
		endif()
		target_compile_definitions("${PROJECT_NAME}_${TEST_NAME}" PRIVATE
			CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
		)
		target_link_libraries("${PROJECT_NAME}_${TEST_NAME}" PRIVATE
			glad-gl
			${LIB_NAME}
			${X11_LIBRARIES}
		)
		target_include_directories("${PROJECT_NAME}_${TEST_NAME}" PRIVATE
			"${EXTERNAL}" ${glad_INCLUDE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad-gl/include")
		add_test("${PROJECT_NAME}_${TEST_NAME}" ${TEST_NAME})
	endforeach()
endif()