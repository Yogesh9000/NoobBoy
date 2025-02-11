cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(playground)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
