cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../CMakeVars.cmake)

# Project Definition
project(test_hkl VERSION ${PROJECT_VERSION})

# External Dependencies
find_package(GTest CONFIG REQUIRED)

# Include here not to confused with actual project include directories
include_directories(${EXTERNAL_LIB_DIR}/googletest/googletest/include)
link_directories(${EXTERNAL_LIB_DIR}/googletest/build/lib)

# Internal dependencies to test modules
set(TEST_MODULE_DIR ${PROJECT_ROOT_DIR}/server/core/hkl)
set(MY_INCLUDE_DIR ${TEST_MODULE_DIR}/../inc ${COMMON_SERVER_DIR}/inc)
set(MY_LIB_DIR ${TEST_MODULE_DIR}/../lib)

# Actual Project files and executables
file(GLOB all_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

# Include + Linking directories for current project
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR} ${TESTSUITE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread gtest gtest_main hkl)

# Tutorial: https://www.youtube.com/watch?v=mdkVnmj32ZQ
# Adding google test to be discovered by ctest
#include(GoogleTest)
#gtest_discover_tests(${PROJECT_NAME})
add_test(${PROJECT_NAME} ${PROJECT_NAME})