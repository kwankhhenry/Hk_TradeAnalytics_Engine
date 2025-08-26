cmake_minimum_required(VERSION 3.16.3)

# Include Common Variables
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../CMakeVars.cmake)

# Project Definition
project(test_src VERSION ${PROJECT_VERSION})

# External Dependencies
find_package(IcecreamCpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Include here not to confused with actual project include directories
include_directories(${IcecreamCpp_INCLUDE_DIRS})
include_directories(${EXTERNAL_LIB_DIR}/googletest/googletest/include)
link_directories(${EXTERNAL_LIB_DIR}/googletest/build/lib)

# Internal dependencies to test modules
set(TEST_MODULE_DIR ${PROJECT_ROOT_DIR}/server)
set(COMMON_DIR ${TEST_MODULE_DIR}/common)
set(MY_INCLUDE_DIR ${TEST_MODULE_DIR}/inc ${COMMON_DIR}/inc)
set(MY_LIB_DIR ${TEST_MODULE_DIR}/lib)

# Actual Project files and executables
add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
    ${TEST_MODULE_DIR}/src/ThreadWorker.cpp
    ${TEST_MODULE_DIR}/src/ThreadPool.cpp
    )

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR} ${TEST_MODULE_DIR}/src)
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main pthread)

# Submodules from this level
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)

# Tutorial: https://www.youtube.com/watch?v=mdkVnmj32ZQ
# Adding google test to be discovered by ctest
add_test(${PROJECT_NAME} ${PROJECT_NAME})