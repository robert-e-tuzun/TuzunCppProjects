# JonesConjecNonAlg/PartialKnotSpec/CMakeLists.txt

# Set the project name and version.
project(PartialKnotSpec VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES
    src/PartialKnotSpecManager.cpp
    src/PartitionBuilder.cpp
    src/PartitionBuilderWrapper.cpp
    src/RepresentativeChecker.cpp
    src/CandidateCtSpecBuilder.cpp
   )

add_library(PartialKnotSpec ${SOURCE_FILES})

target_include_directories(PartialKnotSpec
    PRIVATE include
    PRIVATE ${CMAKE_SOURCE_DIR}/BlkbdJonesConjNonAlg/include
    PRIVATE ${CMAKE_SOURCE_DIR}/Polyh/include
)

target_link_libraries(PartialKnotSpec TuzunUtil CombinCommon MathCommon
       InputOutput BlkbdJonesConjNonAlg Polyh)

#add_subdirectory(test)

