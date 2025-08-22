file(GLOB_RECURSE IXX CONFIGURE_DEPENDS "ixx/*.ixx")
file(GLOB_RECURSE CXX CONFIGURE_DEPENDS "cxx/*.cxx")

if(IXX)
	add_library(${PROJECT_NAME})
	set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD 26
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		CXX_SCAN_FOR_MODULES ON
	)
	target_sources(${PROJECT_NAME}
		PUBLIC FILE_SET m TYPE CXX_MODULES FILES ${IXX}
		PRIVATE ${CXX}
	)
	if(ipo_supported AND NOT (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
		set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
	endif()
	target_link_libraries(${PROJECT_NAME} PUBLIC
		OpenGL::EGL
		${X11_LIBRARIES}
	)
	target_compile_definitions(${PROJECT_NAME} PUBLIC
		CMAKE_COMMAND="${CMAKE_COMMAND}"
		CMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}"
		CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
		CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
	)
	target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall -Wextra -Wpedantic
		# -Weffc++
		# -Wabi-tag
		-Wcomma-subscript
		-Wctad-maybe-unsupported
		-Wctor-dtor-privacy
		-Wdangling-reference
		-Wdelete-non-virtual-dtor
		-Wdeprecated-copy
		-Wdeprecated-literal-operator
		-Wdeprecated-variadic-comma-omission
		-Winvalid-constexpr
		-Winvalid-imported-macros
		-Wnoexcept
		-Wclass-memaccess
		-Wnon-virtual-dtor
		-Wregister
		-Wreorder
		-Wpessimizing-move
		-Wredundant-move
		-Wrange-loop-construct
		-Wredundant-tags
		-Wstrict-null-sentinel
		-Wold-style-cast
		-Woverloaded-virtual
		-Wsign-promo
		-Wmismatched-new-delete
		-Wmismatched-tags
		-Wtemplate-names-tu-local
		-Wvolatile
		-Waligned-new
		-Wplacement-new=2
		-Wcatch-value=3
		-Wconditionally-supported
		-Wextra-semi
		-Wsized-deallocation
		-Wsuggest-final-types
		-Wsuggest-final-methods
		-Wsuggest-override
	)
endif()