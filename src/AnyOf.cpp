//
// Created by renaud.rwemalika on 7/12/2022.
//

#include "cliargs.h"

namespace cliargs {
    bool AnyOf::isValid() const {
        return true;
    }

    bool AnyOf::isRequired() const {
        return false;
    }

    std::string AnyOf::toString() const {
        return {};
    }
} // cliargs