# JonesConjecNonAlg/Polyh/CMakeLists.txt

# Set the project name and version.
project(PolyhSpec VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    src/PolyhManager.cpp
   )

add_library(Polyh ${SOURCE_FILES})

target_include_directories(Polyh
    PRIVATE include
    PRIVATE ${CMAKE_SOURCE_DIR}/BlkbdJonesConjNonAlg/include
)

target_link_libraries(Polyh KnotGraph TuzunUtil InputOutput
       BlkbdJonesConjNonAlg)

#add_subdirectory(test)

