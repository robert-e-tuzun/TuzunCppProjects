# JonesConjecNonAlg/JonesConjNonAlg/CMakeLists.txt

# Set the project name and version.
project(JonesConjNonAlg VERSION 1.0 LANGUAGES CXX)

# --------------------------------------------------------
#
# Set up executable.

add_executable(JonesConjNonAlg
               src/JonesConjNonAlg.cpp
               src/JonesConjNonAlgCompRoot.cpp
               src/JonesConjNonAlgApp.cpp
               src/InitializerNonAlg.cpp
              )

target_link_libraries(JonesConjNonAlg
                      TuzunUtil
                      MathCommon
                      BlkbdJonesConjNonAlg
                      PartialKnotSpec
                      Polyh
                      KnotGraph
                     )

message(STATUS "${PROJECT_SOURCE_DIR}/include")
message(STATUS "${CMAKE_SOURCE_DIR}/include")

target_include_directories(JonesConjNonAlg
    PRIVATE ${CMAKE_SOURCE_DIR}/BlkbdJonesConjNonAlg/include
    PRIVATE ${CMAKE_SOURCE_DIR}/Polyh/include
    PRIVATE ${CMAKE_SOURCE_DIR}/PartialKnotSpec/include
    PRIVATE ${CMAKE_SOURCE_DIR}/KnotGraph/include
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# --------------------------------------------------------
#
# Install the executable.

install(TARGETS JonesConjNonAlg
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
       )

# add_subdirectory(test)

