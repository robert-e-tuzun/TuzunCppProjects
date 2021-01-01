# KnotCommon/KnotGraph/CMakeLists.txt

# Set the project name and version.
project(KnotGraph VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    src/ConwayLikeGraph.cpp
    src/ConwayLikeGraphFactory.cpp
   )

add_library(KnotGraph ${SOURCE_FILES})

target_include_directories(KnotGraph
    PRIVATE include
)

target_link_libraries(KnotGraph MathCommon TuzunUtil)

# Install and export the library.

InstallExportLib(KnotGraph
                 "${CMAKE_INSTALL_LIBDIR}"
                 "${CMAKE_INSTALL_BINDIR}"
                 "${CMAKE_INSTALL_INCLUDEDIR}"
                )

add_subdirectory(test)

