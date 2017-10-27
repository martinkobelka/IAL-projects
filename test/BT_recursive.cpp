#include "gtest/gtest.h"

extern "C" {
#include "../src/c401/c401.h"
}

typedef struct {
    char key;
    int value;
} ITEM;


class BTRecursiveTestFixture : public ::testing::Test {

protected:
    tBSTNodePtr TempTree;

    virtual void SetUp() {
        BSTInit(&TempTree);
    }

    virtual void TearDown() {
        BSTDispose(&TempTree);
    }
};

TEST_F(BTRecursiveTestFixture, Inicialization) {


    EXPECT_EQ(
            NULL,
            TempTree
    ) << "Error inicialization of BT_recursive";
}

TEST_F(BTRecursiveTestFixture, InserAndSearchOneElement) {

    BSTInsert(&TempTree, 'K', 10);

    EXPECT_EQ(
            TempTree->BSTNodeCont,
            10
    ) << "Error Error Insert First Element";

    int value = 0;
    BSTSearch(TempTree, 'K', &value);

    EXPECT_EQ(
            value,
            10
    ) << "Error find element in BT_recursive";
}

TEST_F(BTRecursiveTestFixture, InserAndSearchMuchElements) {

    BSTInsert(&TempTree, 'K', 10);
    BSTInsert(&TempTree, 'S', 42);
    BSTInsert(&TempTree, 'F', 69);
    BSTInsert(&TempTree, 'j', 5678);
    BSTInsert(&TempTree, 'e', 77878);
    BSTInsert(&TempTree, ':', 7780);
    BSTInsert(&TempTree, '3', 7678);
    BSTInsert(&TempTree, 'W', 2424);

    int value = 0;
    BSTSearch(TempTree, ':', &value);

    EXPECT_EQ(
            value,
            7780
    ) << "Error find element in BT_recursive";

    BSTSearch(TempTree, 'F', &value);

    EXPECT_EQ(
            value,
            69
    ) << "Error find element in BT_recursive";

}




