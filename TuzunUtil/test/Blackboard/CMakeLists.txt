# TuzunUtil/test/Blackboard/CMakeLists.txt

project(testBlackboard VERSION 1.0 LANGUAGES CXX)

set(BOOST_ROOT $ENV{BOOST_ROOT})
find_package(Boost 1.67.0)

add_executable(testBlackboard
               src/testBlackboard.cpp
               src/A.cpp
               src/BlackboardTester.cpp
              )

target_link_libraries(testBlackboard
                      TuzunUtil
                      ${BOOST}
                     )

target_include_directories(testBlackboard
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

add_test(testBlackboard testBlackboard)
