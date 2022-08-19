//
// Created by renau on 8/19/2022.
//

#include "cliargs/cliargs.h"
#include <gtest/gtest.h>

using namespace cliargs;

TEST(OneOfTest, TestConstructor) {
    OneOf oneOf{};
}

TEST(OneOfTest, TestAddRequiredArgumentTrhows) {
    OneOf oneOf{};
    auto arg = std::make_unique<Argument>("f", "file", "Absolute path of the file");
    arg->setRequired(true);
    EXPECT_THROW(oneOf.add(std::move(arg)), SpecificationException);
}

TEST(OneOfTest, TestAddSingleArgument) {
    OneOf oneOf{};
    auto arg = std::make_unique<Argument>("f", "file", "Absolute path of the file");
    for(const std::shared_ptr<Constraint>& constraint: oneOf){
        EXPECT_EQ("-f (--file)", constraint->toString());
    }
}

TEST(OneOfTest, TestAddSingleGroup) {
    OneOf oneOf{};
    auto child = std::make_unique<OneOf>();
    oneOf.add(std::move(child));

    for(const std::shared_ptr<Constraint>& constraint: oneOf){
        EXPECT_EQ("", constraint->toString());
    }
}