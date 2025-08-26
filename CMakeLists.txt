cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_SOURCE_DIR}/CMakeVars.cmake)

# Project Definition
project(main VERSION ${PROJECT_VERSION})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/server)
add_subdirectory(${PROJECT_SOURCE_DIR}/client)
add_subdirectory(${PROJECT_SOURCE_DIR}/testsuite/tests/server)
#add_subdirectory(${PROJECT_SOURCE_DIR}/testsuite/tests/client)

# Enable testing modules
enable_testing()