//
// Created by renaud.rwemalika on 8/16/2022.
//

#include "cliargs/cliargs.h"
#include <gtest/gtest.h>

using namespace cliargs;

TEST(ArgumentTest, TestToString) {
    Argument argument("f", "file", "Absolute path of the file");
    EXPECT_EQ("-f (--file)", argument.toString());
}

TEST(ArgumentTest, TestDefaultProperties) {
    Argument argument("f", "file", "Absolute path of the file");

    EXPECT_EQ("f", argument.getFlag());
    EXPECT_EQ("file", argument.getName());
    EXPECT_EQ("Absolute path of the file", argument.getDescription());
    EXPECT_TRUE(argument.isRequired());
    EXPECT_TRUE(argument.isValueRequired());
    EXPECT_FALSE(argument.isAcceptsMultipleValues());
}

TEST(ArgumentTest, TestOtherProperties) {
    Argument argument("f", "file", "Absolute path of the file");
    argument.setRequired(false);
    argument.setValueRequired(false);
    argument.setAcceptMultipleValues(true);

    EXPECT_EQ("f", argument.getFlag());
    EXPECT_EQ("file", argument.getName());
    EXPECT_EQ("Absolute path of the file", argument.getDescription());
    EXPECT_FALSE(argument.isRequired());
    EXPECT_FALSE(argument.isValueRequired());
    EXPECT_TRUE(argument.isAcceptsMultipleValues());
}