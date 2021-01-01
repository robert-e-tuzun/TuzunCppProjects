# KnotCommon/InputOutput/CMakeLists.txt

# Set the project name and version.
project(InputOutput VERSION 1.0 LANGUAGES CXX)

#find_package(TuzunUtil
#             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil
#            )

set(SOURCE_FILES
    src/EmbedReader.cpp
    src/getNumPolyh.cpp
    src/PolyhedronReader.cpp
   )

add_library(InputOutput ${SOURCE_FILES})

target_include_directories(InputOutput
    PRIVATE include
)

target_link_libraries(InputOutput TuzunUtil)

# Install and export the library.

InstallExportLib(InputOutput
                 "${CMAKE_INSTALL_LIBDIR}"
                 "${CMAKE_INSTALL_BINDIR}"
                 "${CMAKE_INSTALL_INCLUDEDIR}"
                )

add_subdirectory(test)

