cmake_minimum_required(VERSION 3.16.3)
project(server VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../Internal_lib/include)
set(MY_LIB_DIR ${PROJECT_SOURCE_DIR}/../Internal_lib/lib)
#list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../Internal_lib/lib/cmake)

find_package(Logging REQUIRED)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/../common/*.cpp
        ${PROJECT_SOURCE_DIR}/../common/*.h
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread MyLib::Logging)