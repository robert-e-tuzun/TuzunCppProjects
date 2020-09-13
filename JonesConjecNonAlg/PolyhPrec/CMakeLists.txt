# JonesConjecNonAlg/PolyhPrec/CMakeLists.txt

# Set the project name and version.
project(PolyhSpec VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    src/PolyhPrecManager.cpp
   )

add_library(PolyhPrec ${SOURCE_FILES})

target_include_directories(PolyhPrec
    PRIVATE include
    PRIVATE ${CMAKE_SOURCE_DIR}/BlkbdJonesConjNonAlg/include
)

target_link_libraries(PolyhPrec TuzunUtil InputOutput
       BlkbdJonesConjNonAlg)

#add_subdirectory(test)

