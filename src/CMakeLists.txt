set (target_name sources)

add_library (${target_name} STATIC "")

target_sources (${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/image.cpp"
        "${PROJECT_SOURCE_DIR}/src/fractal.cpp"
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/image.h"
        "${PROJECT_SOURCE_DIR}/include/fractal.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}"
)
