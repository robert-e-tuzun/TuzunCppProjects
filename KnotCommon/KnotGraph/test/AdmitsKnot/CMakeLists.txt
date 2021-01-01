# KnotCommon/KnotGraph/test/AdmitsKnot/CMakeLists.txt

project(testAdmitsKnot VERSION 1.0 LANGUAGES CXX)

set(BOOST_ROOT $ENV{BOOST_ROOT})
find_package(Boost 1.67.0)

find_package(TuzunUtil
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil)
find_package(MathCommon
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/MathCommon)

add_executable(testAdmitsKnot
               src/testAdmitsKnot.cpp
              )

target_link_libraries(testAdmitsKnot
                      MathCommon
                      KnotGraph
                      TuzunUtil
                      ${BOOST}
                     )

target_include_directories(testAdmitsKnot
        PRIVATE ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_SOURCE_DIR}/KnotGraph/include
)

add_test(testAdmitsKnot testAdmitsKnot)

