file(GLOB STATIC_LIB_SRC
    "*.cpp"
)

file(GLOB STATIC_LIB_H
    "*.(h|hpp)"
)

add_library(
	${OUTPUT_LIB}
	STATIC
	${STATIC_LIB_SRC}
)

target_sources(
	${OUTPUT_LIB}
	PRIVATE
		${STATIC_LIB_SRC}
	PUBLIC
		${STATIC_LIB_H}
)

target_include_directories(
	${OUTPUT_LIB}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)

# Setting this to the library only avoids errors in 3rd party dependencies which are compile with e.g. -Werror
target_compile_options(${OUTPUT_LIB} PUBLIC -Wall -pedantic)

# Include code-coverage settings:
target_link_libraries(
	${OUTPUT_LIB}
	PUBLIC
		coverage_config
)