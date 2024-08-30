cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${PROJECT_SOURCE_DIR}/server)
add_subdirectory(${PROJECT_SOURCE_DIR}/client)