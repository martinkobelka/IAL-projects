cmake_minimum_required(VERSION 3.0)

project(c_start)

include(test/CMakeLists.txt)
enable_testing()

add_executable(unit_tests test/test.cpp)
target_link_libraries(unit_tests gtest)
add_test(NAME test COMMAND unit_tests)

set(SOURCE_FILES_STACK src/c202-test.c src/c202.c src/c202.h)
add_executable(stack ${SOURCE_FILES_STACK})

set(SOURCE_FILES_LINEAR_LIST src/c206.c src/c206-test.c src/c206.h)
add_executable(linear_list ${SOURCE_FILES_LINEAR_LIST})