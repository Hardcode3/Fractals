set (target_name sources)

add_library (${target_name} STATIC "")

target_sources (${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/mandelbrot.cpp"
        "${PROJECT_SOURCE_DIR}/src/misc.cpp"
        "${PROJECT_SOURCE_DIR}/src/image.cpp"
	  "${PROJECT_SOURCE_DIR}/src/julia.cpp"
        "${PROJECT_SOURCE_DIR}/src/sequence.cpp"
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/mandelbrot.h"
        "${PROJECT_SOURCE_DIR}/include/misc.h"
        "${PROJECT_SOURCE_DIR}/include/image.h"
        "${PROJECT_SOURCE_DIR}/include/julia.h"
        "${PROJECT_SOURCE_DIR}/include/sequence.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}"
)