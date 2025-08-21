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
			${LIB_NAME})
		target_include_directories("${PROJECT_NAME}_${TEST_NAME}" PRIVATE
			"${EXTERNAL}")
		add_test("${PROJECT_NAME}_${TEST_NAME}" ${TEST_NAME})
	endforeach()
endif()