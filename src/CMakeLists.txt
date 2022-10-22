set (target_name sources)

add_library (${target_name} STATIC "")

target_sources (${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/mandelbrot_set.cpp"
        "${PROJECT_SOURCE_DIR}/src/misc.cpp"
        "${PROJECT_SOURCE_DIR}/src/image.cpp"
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/mandelbrot_set.h"
        "${PROJECT_SOURCE_DIR}/include/misc.h"
        "${PROJECT_SOURCE_DIR}/include/image.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}"
)