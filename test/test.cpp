#include "gtest/gtest.h"


class SampleTestFixture : public ::testing::Test {
protected:
};

TEST_F(SampleTestFixture, multiplied_answer_to_everything) {
    EXPECT_EQ(
            0,
            0
    );
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}