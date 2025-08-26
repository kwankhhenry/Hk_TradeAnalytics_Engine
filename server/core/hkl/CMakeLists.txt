cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../CMakeVars.cmake)

# Project Definition
project(hkl VERSION ${PROJECT_VERSION})

# Internal dependencies
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
set(MY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../inc ${COMMON_DIR}/inc)
set(MY_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# Actual Project files and executables
file(GLOB all_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        )

add_library(${PROJECT_NAME} SHARED ${all_SRCS})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib      # for shared libraries (.so/.dylib)
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib      # for static libraries (.a)
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin      # for executables (if any)
)

# Include + Linking directories for current project
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)