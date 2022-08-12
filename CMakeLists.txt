cmake_minimum_required(VERSION 3.10)

# set the project name
project(math++)

# add the executable
add_executable(${PROJECT_NAME} math++/math++.cpp)

add_library(
    basic_math_operations
    basic_math_operations/basic_math_operations.hpp
    basic_math_operations/basic_math_operations.cpp
)

target_link_libraries(math++ curl)
target_link_libraries(math++ basic_math_operations)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3 -static-libstdc++")
