cmake_minimum_required(VERSION 2.8.12...3.24)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

project ("fractals" VERSION 1.0)

configure_file (cmake/fractalsConfigure.h.in fractalsConfigure.h)

option (IMGUI_TEST_WITH_EXECUTABLES "Compile mains" ON)
option (IMGUI_TEST_WITH_TESTS "Compile tests" ON)

add_subdirectory (src)

if (IMGUI_TEST_WITH_EXECUTABLES)
    message (STATUS "Configuring imgui_test with executables")
    add_subdirectory (mains)
endif ()

if (IMGUI_TEST_WITH_TESTS)
    enable_testing ()
    message (STATUS "Configuring imgui_test with tests")
    add_subdirectory (tests)
endif ()

