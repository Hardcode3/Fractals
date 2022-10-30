cmake_minimum_required(VERSION 3.10)

if(NOT TARGET sources)
    project(fractals VERSION 1.0)
    find_package(sources REQUIRED CONFIG)
    enable_testing()
endif()

add_executable (test_image test_image.cpp)
target_link_libraries (test_image PUBLIC sources)
add_test (NAME test_image COMMAND test_image)

add_executable (test_misc test_misc.cpp)
target_link_libraries (test_misc PUBLIC sources)
add_test (NAME test_misc COMMAND test_misc)