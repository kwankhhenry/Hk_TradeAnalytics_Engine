cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O5")

add_subdirectory(${PROJECT_SOURCE_DIR}/server)
add_subdirectory(${PROJECT_SOURCE_DIR}/client)