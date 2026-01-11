cmake_minimum_required(VERSION 3.16)
project(computationalGeometry LANGUAGES CXX)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Build common library
add_library(common
    common/Vec3.cpp
    common/Utility.cpp
    common/TextFile.cpp
)
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR}/common)

# Add problems
add_subdirectory(1.line-triangle-intersection)
add_subdirectory(2.star-polygon)