cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeVars.cmake)

# Project Definition
project(client VERSION ${PROJECT_VERSION})

# External dependencies

# Internal dependencies
set(MY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/inc ${COMMON_CLIENT_DIR}/inc)
set(MY_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

# Find custom package
find_package(Logging REQUIRED)

file(GLOB all_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread MyLib::Logging)