cmake_minimum_required(VERSION 3.10)

if(NOT TARGET fractals)
    project(fractals VERSION 1.0)
    find_package(sources REQUIRED CONFIG)
    enable_testing()
endif()


