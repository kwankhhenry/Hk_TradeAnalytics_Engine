# Definition of common variables used across project

# CMake Project Settings
set(PROJECT_NAME "Hk_TradeAnalytics_Engine")
set(PROJECT_VERSION "1.0.0")
set(PROJECT_ROOT_DIR /home/admin/Outside_Project/Hk_TradeAnalytics_Engine)

# Compilation Settings
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.16.3)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# External Dependencies for gtest
set(EXTERNAL_LIB_DIR /home/admin/External_lib)
set(INTERNAL_LIB_DIR /home/admin/Home_Project/Internal_lib)

# Note: redfine e.g.
#       -DCMAKE_INSTALL_PREFIX=/home/admin/External_lib 
#       -DCMAKE_INSTALL_LIBDIR=/home/admin/External_lib/lib 
#       -DCMAKE_INSTALL_INCLUDEDIR=/home/admin/External_lib/include
# if you wanna custom install file locations
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_LIB_DIR}/lib/cmake ${INTERNAL_LIB_DIR}/lib/cmake)