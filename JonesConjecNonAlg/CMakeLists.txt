#  JonesConjecNonAlg/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name and version.
project(JonesConjecNonAlg VERSION 1.0 LANGUAGES CXX)

# Include internal libraries.
find_package(TuzunUtil
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil
            )
find_package(CombinCommon
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/CombinCommon
            )
find_package(MathCommon
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/MathCommon
            )
find_package(BlkbdKnot
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/KnotCommon
            )
find_package(InputOutput
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/KnotCommon
            )
find_package(KnotGraph
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/KnotCommon
            )

# Include third party libraries.
find_package(Boost REQUIRED)

# Enable testing, and add subdirectories in order of dependence (lower
# may depend on upper, but not vice versa).
enable_testing()
add_subdirectory(BlkbdJonesConjNonAlg)
add_subdirectory(Polyh)
add_subdirectory(PartialKnotSpec)
add_subdirectory(JonesConjNonAlg)

