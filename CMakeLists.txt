cmake_minimum_required(VERSION 3.28.0)
project(learncpp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(learncpp main.cpp
#Point.cpp
Vec3.cpp
Utility.cpp
)

# target_precompile_headers(learncpp PUBLIC
# <vector>
# <iostream>
# "Vec3.h"
# )
