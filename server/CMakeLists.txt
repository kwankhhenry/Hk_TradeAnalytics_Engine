cmake_minimum_required(VERSION 3.16.3)
project(server VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

# Useful alias
set(EXTERNAL_LIB_DIR /home/admin/External_lib)
set(MY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../Internal_lib/include)
set(MY_LIB_DIR ${PROJECT_SOURCE_DIR}/../Internal_lib/lib)

# Note: redfine e.g.
#       -DCMAKE_INSTALL_PREFIX=/home/admin/External_lib 
#       -DCMAKE_INSTALL_LIBDIR=/home/admin/External_lib/lib 
#       -DCMAKE_INSTALL_INCLUDEDIR=/home/admin/External_lib/include
# if you wanna custom install file locations
# Find icecream package (Config Mode)
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_LIB_DIR}/lib/cmake)
find_package(IcecreamCpp CONFIG REQUIRED)

# Include here not to confused with actual project include directories
include_directories(${IcecreamCpp_INCLUDE_DIRS})

# Find custom package
find_package(Logging REQUIRED)

# Actual Project files and executables
file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/../common/*.cpp
        ${PROJECT_SOURCE_DIR}/../common/*.h
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${MY_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread MyLib::Logging)

# Enable testing modules
enable_testing()
add_subdirectory(tests)