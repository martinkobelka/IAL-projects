#include "gtest/gtest.h"


extern "C" {
#include "../src/c206/c206.h"
extern int errflg;
}

class LinearListTestFixture : public ::testing::Test {
protected:
    tDLList *ptr_list;

    virtual void SetUp() {
        ptr_list = (tDLList *) malloc(sizeof(tDLList));
        errflg = 0;
        DLInitList(ptr_list);
    }

    virtual void TearDown() {
        DLDisposeList(ptr_list);
        free(ptr_list);
    }

};

TEST_F(LinearListTestFixture, Inicialization) {

    EXPECT_EQ(
            NULL,
            ptr_list->First
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last
    );

}

TEST_F(LinearListTestFixture, InsertFirstOneItem) {

    DLInsertFirst(ptr_list, 31);

    EXPECT_EQ(
            31,
            ptr_list->First->data
    );

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Act
    );

}

TEST_F(LinearListTestFixture, InsertFirstMoreItems) {

    DLInsertFirst(ptr_list, 31);
    DLInsertFirst(ptr_list, 41);

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            ptr_list->Last,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );


    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

}

TEST_F(LinearListTestFixture, InsertLastOneItem) {

    DLInsertLast(ptr_list, 31);

    EXPECT_EQ(
            31,
            ptr_list->First->data
    );

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Act
    );

}

TEST_F(LinearListTestFixture, InsertLastMoreItems) {

    DLInsertLast(ptr_list, 31);
    DLInsertLast(ptr_list, 41);

    EXPECT_EQ(
            ptr_list->First->data,
            31
    );

    EXPECT_EQ(
            ptr_list->Last->data,
            41
    );

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            ptr_list->Last,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );


    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

}

TEST_F(LinearListTestFixture, SetActivityFirst) {

    DLInsertLast(ptr_list, 31);
    DLInsertLast(ptr_list, 41);

    DLFirst(ptr_list);

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Act
    );

    EXPECT_EQ(
            ptr_list->Act->data,
            31
    );

}


TEST_F(LinearListTestFixture, SetActivityLast) {

    DLInsertLast(ptr_list, 31);
    DLInsertLast(ptr_list, 41);

    DLLast(ptr_list);

    EXPECT_EQ(
            ptr_list->Last,
            ptr_list->Act
    );

    EXPECT_EQ(
            ptr_list->Act->data,
            41
    );

}

TEST_F(LinearListTestFixture, DLCopyFirst) {

    int value;
    DLCopyFirst(ptr_list, &value);

    EXPECT_EQ(
            errflg,
            1
    );

    DLInsertLast(ptr_list, 31);
    DLInsertLast(ptr_list, 41);


    DLCopyFirst(ptr_list, &value);

    EXPECT_EQ(
            value,
            31
    );

}

TEST_F(LinearListTestFixture, DlCopyLast) {

    int value;
    DLCopyLast(ptr_list, &value);

    EXPECT_EQ(
            errflg,
            1
    );

    DLInsertLast(ptr_list, 31);
    DLInsertLast(ptr_list, 41);


    DLCopyLast(ptr_list, &value);

    EXPECT_EQ(
            value,
            41
    );

}

TEST_F(LinearListTestFixture, DeleteFirst) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);

    DLFirst(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLDeleteFirst(ptr_list);

    EXPECT_EQ(
            DLActive(ptr_list),
            0
    );

    EXPECT_EQ(
            41,
            ptr_list->First->data
    );

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Act
    );

}

TEST_F(LinearListTestFixture, DeleteLast) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);

    DLLast(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLDeleteLast(ptr_list);

    EXPECT_EQ(
            DLActive(ptr_list),
            0
    );

    EXPECT_EQ(
            31,
            ptr_list->First->data
    );

    EXPECT_EQ(
            ptr_list->First,
            ptr_list->Last
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->lptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Last->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Act
    );

}

TEST_F(LinearListTestFixture, ListActive) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);
    DLInsertLast(ptr_list, 51);

    DLFirst(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLPred(ptr_list);

    EXPECT_EQ(
            DLActive(ptr_list),
            0
    );

    DLFirst(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLSucc(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLSucc(ptr_list);

    EXPECT_NE(
            DLActive(ptr_list),
            0
    );

    DLSucc(ptr_list);

    EXPECT_EQ(
            DLActive(ptr_list),
            0
    );


}

TEST_F(LinearListTestFixture, TestActualize) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);
    DLInsertLast(ptr_list, 51);

    DLFirst(ptr_list);

    DLSucc(ptr_list);

    DLActualize(ptr_list, 111);

    EXPECT_EQ(
            ptr_list->Act->data,
            111
    );

    EXPECT_EQ(
            ptr_list->First->rptr->data,
            111
    );

    DLFirst(ptr_list);
    DLPred(ptr_list);

    DLActualize(ptr_list, 111);

    EXPECT_EQ(
            errflg,
            0
    );

}

TEST_F(LinearListTestFixture, TestCopyValue) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);
    DLInsertLast(ptr_list, 51);

    DLFirst(ptr_list);

    int value;
    DLCopy(ptr_list, &value);

    EXPECT_EQ(
            value,
            31
    );

    DLSucc(ptr_list);

    DLCopy(ptr_list, &value);

    EXPECT_EQ(
            value,
            41
    );

    DLSucc(ptr_list);

    DLCopy(ptr_list, &value);

    EXPECT_EQ(
            value,
            51
    );

    DLSucc(ptr_list);

    DLCopy(ptr_list, &value);

    EXPECT_EQ(
            errflg,
            1
    );
}

TEST_F(LinearListTestFixture, TestPreDeleteAndPostDelete) {

    DLInsertFirst(ptr_list, 31);
    DLInsertLast(ptr_list, 41);
    DLInsertLast(ptr_list, 51);

    DLFirst(ptr_list);
    DLSucc(ptr_list);

    DLPreDelete(ptr_list);

    EXPECT_EQ(
            ptr_list->First->data,
            41
    );

    DLPostDelete(ptr_list);

    EXPECT_EQ(
            ptr_list->Last->data,
            41
    );

    EXPECT_EQ(
            ptr_list->Last,
            ptr_list->First
    );

    EXPECT_EQ(
            NULL,
            ptr_list->Act->rptr
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->lptr
    );


}

TEST_F(LinearListTestFixture, CopyFirstAndLast) {

    DLInsertFirst(ptr_list, 31);
    DLInsertFirst(ptr_list, 41);
    DLInsertFirst(ptr_list, 51);

    int value;
    DLCopyFirst(ptr_list, &value);

    EXPECT_EQ(
            value,
            51
    );

    DLCopyLast(ptr_list, &value);

    EXPECT_EQ(
            value,
            31
    );

    for (int i = 0; i < 3; i++)
        DLDeleteFirst(ptr_list);

    DLCopyFirst(ptr_list, &value);

    EXPECT_EQ(
            errflg,
            1
    );

    errflg = 0;

    DLCopyLast(ptr_list, &value);

    EXPECT_EQ(
            errflg,
            1
    );

}

TEST_F(LinearListTestFixture, AddAfterAct) {

    DLInsertFirst(ptr_list, 31);

    DLFirst(ptr_list);

    DLPostInsert(ptr_list, 42);

    EXPECT_EQ(
            ptr_list->First->data,
            31
    );

    EXPECT_EQ(
            ptr_list->First->rptr->data,
            42
    );

    EXPECT_EQ(
            NULL,
            ptr_list->First->rptr->rptr
    );

    DLPostInsert(ptr_list, 12);

    EXPECT_EQ(
            ptr_list->First->data,
            31
    );

    EXPECT_EQ(
            ptr_list->First->rptr->data,
            12
    );

    EXPECT_EQ(
            ptr_list->First->rptr->rptr->data,
            42
    );

}

TEST_F(LinearListTestFixture, AddBeforeAct) {

    DLInsertFirst(ptr_list, 31);

    EXPECT_EQ(
            ptr_list->First->data,
            31
    );

    DLFirst(ptr_list);

    DLPreInsert(ptr_list, 42);

    EXPECT_EQ(
            ptr_list->First->data,
            42
    );

    EXPECT_EQ(
            ptr_list->First->rptr->data,
            31
    );

    DLPreInsert(ptr_list, 12);

    EXPECT_EQ(
            ptr_list->First->data,
            42
    );

    EXPECT_EQ(
            ptr_list->First->rptr->data,
            12
    );

    EXPECT_EQ(
            ptr_list->First->rptr->rptr->data,
            31
    );

}