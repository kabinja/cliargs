//
// Created by renaud.rwemalika on 7/28/2022.
//

#include "cliargs.h"

namespace cliargs {
    bool OneOf::isValid() const {
        return false;
    }

    GroupConstraint &OneOf::add(std::unique_ptr<Constraint> constraint) {
        if (constraint->isRequired()) {
            throw SpecificationException(
                    "Required arguments are not allowed"
                    " in an exclusive grouping.",
                    constraint->toString());
        }

        return GroupConstraint::add(std::move(constraint));
    }
}