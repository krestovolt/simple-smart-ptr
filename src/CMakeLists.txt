file(GLOB STATIC_LIB_SRC
    "*.cpp"
)

file(GLOB STATIC_LIB_H
    "*.h"
)

ADD_LIBRARY(
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