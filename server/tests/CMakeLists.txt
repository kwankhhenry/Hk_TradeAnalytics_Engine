cmake_minimum_required(VERSION 3.16.3)
project(testing VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Useful alias
set(EXTERNAL_LIB_DIR /home/admin/External_lib)

# Note: redfine e.g.
#       -DCMAKE_INSTALL_PREFIX=/home/admin/External_lib 
#       -DCMAKE_INSTALL_LIBDIR=/home/admin/External_lib/lib 
#       -DCMAKE_INSTALL_INCLUDEDIR=/home/admin/External_lib/include
# if you wanna custom install file locations
# Find icecream package (Config Mode)
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_LIB_DIR}/lib/cmake)
find_package(IcecreamCpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Include here not to confused with actual project include directories
include_directories(${IcecreamCpp_INCLUDE_DIRS})
include_directories(/home/admin/External_lib/googletest/googletest/include)
link_directories(/home/admin/External_lib/googletest/build/lib)

# Actual Project files and executables
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/test.cpp
    ${PROJECT_SOURCE_DIR}/../src/ThreadWorker.cpp
    ${PROJECT_SOURCE_DIR}/../src/ThreadPool.cpp)

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/../)
target_link_directories(${PROJECT_NAME} PRIVATE )
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main pthread)

# Tutorial: https://www.youtube.com/watch?v=mdkVnmj32ZQ
# Adding google test to be discovered by ctest
add_test(Project_${PROJECT_NAME} ${PROJECT_NAME})