set (target_name sources)

add_library (${target_name} STATIC "")

target_sources (${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/julia.cpp"
        "${PROJECT_SOURCE_DIR}/src/mandelbrot.cpp"
        "${PROJECT_SOURCE_DIR}/src/fractals.cpp"
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/julia.hpp"
        "${PROJECT_SOURCE_DIR}/include/mandelbrot.hpp"
        "${PROJECT_SOURCE_DIR}/include/fractals.hpp"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/externals/lodepng"
        "${PROJECT_BINARY_DIR}"
)

target_link_libraries(
    ${target_name} PRIVATE lodepng
)