#include "gtest/gtest.h"

extern "C" {
#include "../src/c202.h"
int err_flag;
}


class StackTestFixture : public ::testing::Test {

protected:
    tStack *ptrstack;

    virtual void SetUp() {
        ptrstack = (tStack *) malloc(sizeof(tStack));
        stackInit(ptrstack);
        err_flag = 0;
    }

    virtual void TearDown() {
        free(ptrstack);
    }
};

TEST_F(StackTestFixture, Inicialization) {

    tStack *null_ = NULL;

    stackInit(null_);

    EXPECT_EQ(
            err_flag,
            1
    ) << "Error inicialization of stack";


    EXPECT_EQ(
            ptrstack->top,
            -1
    ) << "Error inicialization of stack";
}

TEST_F(StackTestFixture, AddEasy) {

    char start_sybmol = '0' - 1;

    for (int i = 0; i < STACK_SIZE; i++) {

        stackPush(ptrstack, ++start_sybmol);
    }


    char actual_symbol;
    stackTop(ptrstack, &actual_symbol);

    for (int i = 0; i < STACK_SIZE; i++) {
        EXPECT_EQ(
                actual_symbol,
                start_sybmol--
        ) << "Error popping element";

        stackPop(ptrstack);
        stackTop(ptrstack, &actual_symbol);
    }
}

TEST_F(StackTestFixture, IsEmpty) {

    EXPECT_NE(
            stackEmpty(ptrstack),
            0
    ) << "Error stack empty";

    for (int i = 0; i < STACK_SIZE; i++) {

        stackPush(ptrstack, 'a');

        EXPECT_EQ(
                stackEmpty(ptrstack),
                0
        ) << "Error stack empty";
    }

}

TEST_F(StackTestFixture, IsFull) {
    EXPECT_EQ(
            stackFull(ptrstack),
            0
    ) << "Error stack full";

    for (int i = 1; i < STACK_SIZE; i++) {

        stackPush(ptrstack, 'c');

        EXPECT_EQ(
                stackFull(ptrstack),
                0
        ) << "Error stack full";
    }

    stackPush(ptrstack, 'c');

    EXPECT_NE(
            stackFull(ptrstack),
            0
    ) << "Error stack full";

}

TEST_F(StackTestFixture, TestTop) {

    char char_;

    stackTop(ptrstack, &char_);

    EXPECT_EQ(
            err_flag,
            1
    ) << "Error in function get top";

    stackPush(ptrstack, 'c');

    stackTop(ptrstack, &char_);

    EXPECT_EQ(
            char_,
            'c'
    ) << "Error in function get top";

    stackPop(ptrstack);
}



