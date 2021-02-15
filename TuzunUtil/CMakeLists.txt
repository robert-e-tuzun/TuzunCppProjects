# TuzunUtil/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name and version.
project(TuzunUtil VERSION 1.0.0 LANGUAGES CXX)

# Enable the finding of InstallExportLib.cmake by adding the directory it's
# in to CMAKE_MODULE_PATH.

list(APPEND CMAKE_MODULE_PATH ${MY_MODULES})
include(GNUInstallDirs)
include(InstallExportLib)

# Include Boost.

find_package(Boost REQUIRED)

# Set up the library.

set(SOURCE_FILES
    src/Blackboard.cpp
   )

set(HEADER_FILES
    include/TuzunUtil/Blackboard.h
    include/TuzunUtil/CppDatatypes.h
    include/TuzunUtil/SortByRank.h
   )

add_library(TuzunUtil STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(TuzunUtil
    PUBLIC    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(TuzunUtil ${Boost_LIBRARIES})

# Install and export the library.

InstallExportLib(TuzunUtil "${CMAKE_INSTALL_LIBDIR}"
                 "${CMAKE_INSTALL_BINDIR}"
                 "${CMAKE_INSTALL_INCLUDEDIR}")

# Enable testing and add testing related directory.

enable_testing()
add_subdirectory(test)
