#include "gtest/gtest.h"

extern "C" {
#include "../src/c204.h"
}


class StackIntToPostTestFixture : public ::testing::Test {

protected:

};

TEST_F(StackIntToPostTestFixture, 01) {
    char input_string[] = "A+B=";
    char expected_output[] = "AB+=";
    char *real_output;

    real_output = infix2postfix(input_string);


    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 02) {
    char input_string[] = "A+B*C=";
    char expected_output[] = "ABC*+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";
}

TEST_F(StackIntToPostTestFixture, 03) {
    char input_string[] = "A+B*C=";
    char expected_output[] = "ABC*+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 04) {
    char input_string[] = "(A+B)*C=";
    char expected_output[] = "AB+C*=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 05) {
    char input_string[] = "A+B*C+D=";
    char expected_output[] = "ABC*+D+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}


TEST_F(StackIntToPostTestFixture, 06) {
    char input_string[] = "A+B+C+D=";
    char expected_output[] = "AB+C+D+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 07) {
    char input_string[] = "a+B=";
    char expected_output[] = "aB+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 08) {
    char input_string[] = "0-1=";
    char expected_output[] = "01-=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 09) {
    char input_string[] = "(A*0+b)*((c*(1+D))-(e/(3*f+g)))=";
    char expected_output[] = "A0*b+c1D+*e3f*g+/-*=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 10) {
    char input_string[] = "(A*0+b)*((c*(1+D))-(e/(3*f+g)))=";
    char expected_output[] = "A0*b+c1D+*e3f*g+/-*=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 11) {
    char input_string[] = "A*(b-C)=";
    char expected_output[] = "AbC-*=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}


TEST_F(StackIntToPostTestFixture, 12) {
    char input_string[] = "A*(b/c)=";
    char expected_output[] = "Abc/*=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}

TEST_F(StackIntToPostTestFixture, 13) {
    char input_string[] = "A+(B-c)=";
    char expected_output[] = "ABc-+=";
    char *real_output;

    real_output = infix2postfix(input_string);

    EXPECT_STREQ(
            expected_output,
            real_output
    ) << "Error debile";

    free(real_output);
}