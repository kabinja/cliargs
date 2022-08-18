//
// Created by renau on 8/17/2022.
//

#include "cliargs/cliargs.h"
#include <gtest/gtest.h>

using namespace cliargs;

TEST(AnyOf, constructor) {
    AnyOf anyOf{};
}

TEST(AnyOf, add_single_argument) {
    AnyOf anyOf{};
    auto arg = std::make_unique<Argument>("f", "file", "Absolute path of the file");
    anyOf.add(std::move(arg));

    for(const std::shared_ptr<Constraint>& constraint: anyOf){
        EXPECT_EQ("-f (--file)", constraint->toString());
    }
}