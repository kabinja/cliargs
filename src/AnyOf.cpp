//
// Created by renaud.rwemalika on 7/12/2022.
//

#include "cliargs/cliargs.h"

namespace cliargs {
    bool AnyOf::isRequired() const {
        return false;
    }

    std::string AnyOf::toString() const {
        return {};
    }
} // cliargs