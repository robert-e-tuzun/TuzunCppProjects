# KnotCommon/InputOutput/test/EmbedReader/CMakeLists.txt

project(testEmbedReader VERSION 1.0 LANGUAGES CXX)

set(BOOST_ROOT $ENV{BOOST_ROOT})
find_package(Boost 1.67.0)

find_package(TuzunUtil
             PATHS ${CMAKE_INSTALL_PREFIX}/lib/cmake/TuzunUtil
            )

add_executable(testEmbedReader
               src/testEmbedReader.cpp
              )

target_link_libraries(testEmbedReader
                      InputOutput
                      TuzunUtil
                      ${BOOST}
                     )

target_include_directories(testEmbedReader
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/InputOutput/include
)

find_program(BASH_PROGRAM bash)

if (BASH_PROGRAM)
   add_test(testScriptEmbedReader
            ${BASH_PROGRAM}
            ${CMAKE_CURRENT_SOURCE_DIR}/a.x
           )
endif (BASH_PROGRAM)
