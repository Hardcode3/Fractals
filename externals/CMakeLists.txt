
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lodepng)
    execute_process(
        COMMAND git clone https://github.com/lvandeve/lodepng.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    message("> Cloning lodepng from remote")
else()
    message("> Lodepng already cloned, proceeding")
endif()

add_subdirectory(imgui)

# add the library here
set(LODEPNG_SRC
    #${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_benchmark.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_fuzzer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_unittest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_util.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/pngdetail.cpp
)

add_library(lodepng ${LODEPNG_SRC})
target_include_directories(lodepng PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng
)
