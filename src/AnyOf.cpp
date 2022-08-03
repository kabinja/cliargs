//
// Created by renaud.rwemalika on 7/12/2022.
//

#include "cliargs.h"
#include "Visitor.h"

namespace cliargs {
    bool AnyOf::isValid() const {
        return true;
    }

    void AnyOf::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    bool AnyOf::isRequired() const {
        return false;
    }
} // cliargs