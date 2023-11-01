cmake_minimum_required(VERSION 3.16)
project(3D_Triangles_intersection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # use CMAKE_CXX_STANDARD
set(SOURCE_LIST main.cpp)

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")

add_executable(
    triangles
    ${SOURCE_LIST}  
)

target_include_directories(triangles PUBLIC ${INCLUDE_DIR})

