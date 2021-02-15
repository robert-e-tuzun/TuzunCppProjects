# CombinCommon/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name and version.
project(CombinCommon VERSION 1.0.0 LANGUAGES CXX)

find_package(TuzunUtil
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil
            )

# Enable the finding of InstallExportLib.cmake by adding the directory it's
# in to CMAKE_MODULE_PATH.

list(APPEND CMAKE_MODULE_PATH ${MY_MODULES})
include(GNUInstallDirs)
include(InstallExportLib)

# Include Boost.

find_package(Boost REQUIRED)

# Set up the library.

set(SOURCE_FILES
    src/KComposition.cpp
    src/BinomCoeffTable.cpp
    src/buildSomeFilteredTransformedCompositions.cpp
    src/Speedometric.cpp
   )

add_library(CombinCommon STATIC ${SOURCE_FILES})

target_include_directories(CombinCommon
    PUBLIC    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(CombinCommon TuzunUtil ${Boost_LIBRARIES})

# Install and export the library.

InstallExportLib(CombinCommon "${CMAKE_INSTALL_LIBDIR}"
                 "${CMAKE_INSTALL_BINDIR}"
                 "${CMAKE_INSTALL_INCLUDEDIR}")

# Enable testing and add testing related directory.

enable_testing()
#add_subdirectory(test)
