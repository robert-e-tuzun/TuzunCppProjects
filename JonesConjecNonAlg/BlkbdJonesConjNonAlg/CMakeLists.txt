# JonesConjecNonAlg/BlkbdJonesConjNonAlg/CMakeLists.txt

# Set the project name and version.
project(BlkbdJonesConjNonAlg VERSION 1.0 LANGUAGES CXX)

# Set up library.
set(SOURCE_FILES
    src/BlkbdRunParamsNonAlg.cpp
    src/GetPointerRunParamsNonAlg.cpp
    src/BlkbdPolyhPrec.cpp
    src/GetPointerPolyhPrec.cpp
   )

add_library(BlkbdJonesConjNonAlg ${SOURCE_FILES})

target_include_directories(BlkbdJonesConjNonAlg
    PRIVATE include
)

target_link_libraries(BlkbdJonesConjNonAlg TuzunUtil)

# Add subdirectories.
#add_subdirectory(test)

