//
// Created by renau on 8/18/2022.
//

#include "cliargs/cliargs.h"
#include <gtest/gtest.h>

using namespace cliargs;

TEST(CommandLineTest, TestConstructor) {
    CommandLine commandLine{};
}

TEST(CommandLineTest, TestValidateOneArgument) {
    auto arg = std::make_unique<Argument>("f", "file", "Absolute path of the file");
    CommandLine commandLine{};
    commandLine.add(std::move(arg));
    commandLine.validate();
}

TEST(CommandLineTest, TestValidateArgsWithSameName) {
    CommandLine commandLine{};
    commandLine.add(std::make_unique<Argument>("f", "file", "Absolute path of the file"));
    commandLine.add(std::make_unique<Argument>("j", "file", "Another absolute path of the file"));

    EXPECT_THROW(commandLine.validate(), ValidationException);
}

TEST(CommandLineTest, TestValidateArgsWithSameFlag) {
    CommandLine commandLine{};
    commandLine.add(std::make_unique<Argument>("f", "file", "Absolute path of the file"));
    commandLine.add(std::make_unique<Argument>("f", "folder", "Absolute path of the folder"));

    EXPECT_THROW(commandLine.validate(), ValidationException);
}

TEST(CommandLineTest, TestValidateArgsWithSameDescription) {
    CommandLine commandLine{};
    commandLine.add(std::make_unique<Argument>("f", "file", "Absolute path of the folder"));
    commandLine.add(std::make_unique<Argument>("d", "folder", "Absolute path of the folder"));

    commandLine.validate();
}

TEST(CommandLineTest, TestEmptyCommandLine) {
    CommandLine commandLine{};
    EXPECT_THROW(commandLine.parse(0, nullptr), ParserException);
}