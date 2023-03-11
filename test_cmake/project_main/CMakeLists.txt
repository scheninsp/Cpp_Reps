cmake_minimum_required(VERSION 3.14)

project(project_main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(project1)
add_subdirectory(project2)

