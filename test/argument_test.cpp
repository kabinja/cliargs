//
// Created by renaud.rwemalika on 8/16/2022.
//

#include "cliargs/cliargs.h"
#include <gtest/gtest.h>

using namespace cliargs;

TEST(ArgumentTest, TestInvalidFlagNotAlphabetic) {
    EXPECT_THROW(Argument("2", "file", "Absolute path of the file"), SpecificationException);
}

TEST(ArgumentTest, TestInvalidFlagNotSingleChar) {
    EXPECT_THROW(Argument("fi", "file", "Absolute path of the file"), SpecificationException);
}

TEST(ArgumentTest, TestToString) {
    Argument argument("f", "file", "Absolute path of the file");
    EXPECT_EQ("-f (--file)", argument.toString());
}

TEST(ArgumentTest, TestToStringWithoutFlag) {
    Argument argument( "file", "Absolute path of the file");
    EXPECT_EQ("(--file)", argument.toString());
}

TEST(ArgumentTest, TestDefaultProperties) {
    Argument argument("f", "file", "Absolute path of the file");

    EXPECT_EQ("f", argument.getFlag());
    EXPECT_EQ("file", argument.getName());
    EXPECT_EQ("Absolute path of the file", argument.getDescription());
    EXPECT_FALSE(argument.isRequired());
    EXPECT_TRUE(argument.isValueRequired());
    EXPECT_FALSE(argument.isAcceptsMultipleValues());
}

TEST(ArgumentTest, TestOtherProperties) {
    Argument argument("f", "file", "Absolute path of the file");
    argument.setRequired(true);
    argument.setValueRequired(false);
    argument.setAcceptMultipleValues(true);

    EXPECT_EQ("f", argument.getFlag());
    EXPECT_EQ("file", argument.getName());
    EXPECT_EQ("Absolute path of the file", argument.getDescription());
    EXPECT_TRUE(argument.isRequired());
    EXPECT_FALSE(argument.isValueRequired());
    EXPECT_TRUE(argument.isAcceptsMultipleValues());
}