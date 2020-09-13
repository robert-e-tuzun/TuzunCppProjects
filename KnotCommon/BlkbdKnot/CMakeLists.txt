# KnotCommon/BlkbdKnot/CMakeLists.txt

# Set the project name and version.
project(BlkbdKnot VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    src/BlkbdPolyhData.cpp
    src/getPointerPolyhData.cpp
   )

add_library(BlkbdKnot ${SOURCE_FILES})

target_include_directories(BlkbdKnot
        PRIVATE include)

target_link_libraries(BlkbdKnot TuzunUtil)

# Install and export the library.

InstallExportLib(BlkbdKnot
                 "${CMAKE_INSTALL_LIBDIR}"
                 "${CMAKE_INSTALL_BINDIR}"
                 "${CMAKE_INSTALL_INCLUDEDIR}"
                )

#add_subdirectory(test)

