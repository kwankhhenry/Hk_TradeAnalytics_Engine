cmake_minimum_required(VERSION 3.16.3)
project(testing VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/test.cpp
    ${PROJECT_SOURCE_DIR}/../src/ThreadWorker.cpp
    ${PROJECT_SOURCE_DIR}/../src/ThreadPool.cpp)

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    /home/admin/External_lib/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/../)
target_link_directories(${PROJECT_NAME} PRIVATE /home/admin/External_lib/googletest/build/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main pthread)

# Tutorial: https://www.youtube.com/watch?v=mdkVnmj32ZQ
# Adding google test to be discovered by ctest
add_test(Project_${PROJECT_NAME} ${PROJECT_NAME})