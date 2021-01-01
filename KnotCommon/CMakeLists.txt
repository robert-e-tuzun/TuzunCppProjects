# KnotCommon/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name and version.
project(KnotCommon VERSION 1.0 LANGUAGES CXX)

find_package(TuzunUtil
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil
            )
find_package(MathCommon
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/MathCommon
            )

# Enable the finding of InstallExportLib.cmake by adding the directory it's
# in to CMAKE_MODULE_PATH.

list(APPEND CMAKE_MODULE_PATH ${MY_MODULES})
include(GNUInstallDirs)
include(InstallExportLib)

# Include Boost.

find_package(Boost REQUIRED)

enable_testing()

# Add subdirectories for libraries.
add_subdirectory(BlkbdKnot)
add_subdirectory(InputOutput)
add_subdirectory(KnotGraph)

