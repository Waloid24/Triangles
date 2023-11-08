cmake_minimum_required(VERSION 3.16)
project(3D_Triangles_intersection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory("test")

