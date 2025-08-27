cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeVars.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/server)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/client)