cmake_minimum_required(VERSION 3.0)

project(c_start)

include(test/CMakeLists.txt)
enable_testing()

add_executable(unit_tests test/stack.cpp test/inf_to_post.cpp test/linear_list.cpp test/BT_recursive.cpp
        src/c202/c202.c src/c202/c202.h src/c204/c204.c src/c204/c204.h src/c206/c206.c src/c206/c206.h
        src/c401/c401.c src/c401/c401.h)
target_link_libraries(unit_tests gtest)
add_test(NAME test COMMAND unit_tests)

set(SOURCE_FILES_STACK src/c202/c202-test.c src/c202/c202.c src/c202/c202.h)
add_executable(stack ${SOURCE_FILES_STACK})

set(SOURCE_FILES_LINEAR_LIST src/c206/c206.c src/c206/c206-test.c src/c206/c206.h)
add_executable(linear_list ${SOURCE_FILES_LINEAR_LIST})

set(SOURCE_FILES_LINEAR_LIST src/c204/c204.c src/c204/c204-test.c src/c204/c204.h src/c202/c202.c src/c202/c202.h)
add_executable(inf_to_pos ${SOURCE_FILES_LINEAR_LIST})

set(SOURCE_FILES_LINEAR_LIST src/c402/c402.c src/c402/c402-test.c src/c402/c402.h)
add_executable(binary_tree_iterative ${SOURCE_FILES_LINEAR_LIST})

set(SOURCE_FILES_LINEAR_LIST src/c401/c401.c src/c401/c401-test.c src/c401/c401.h)
add_executable(binary_tree_recursive ${SOURCE_FILES_LINEAR_LIST})

set(SOURCE_FILES_LINEAR_LIST src/c016/c016.c src/c016/c016-test.c src/c016/c016.h)
add_executable(hash_table ${SOURCE_FILES_LINEAR_LIST})