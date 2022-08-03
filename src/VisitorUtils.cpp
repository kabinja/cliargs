//
// Created by renau on 8/1/2022.
//

#include "VisitorUtils.h"

namespace cliargs {
    void VisitorUtils::traverse(Visitor *visitor, const GroupConstraint *groupConstraint) {
        for(const auto& constraint: *groupConstraint){
            constraint->accept(visitor);
        }
    }
} // cliargs