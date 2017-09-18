cmake_minimum_required(VERSION 3.0)

project(c_start)

include(test/CMakeLists.txt)
enable_testing()

add_executable(unit_tests test/test.cpp)
target_link_libraries(unit_tests gtest)
add_test(NAME test COMMAND unit_tests)

set(SOURCE_FILES src/main.c)
add_executable(untitled ${SOURCE_FILES})