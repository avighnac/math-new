cmake_minimum_required(VERSION 3.10)

# set the project name
project(math++)

# add the executable
add_executable(${PROJECT_NAME} math++.cpp)

target_link_libraries(math++ curl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
