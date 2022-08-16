//
// Created by renau on 8/1/2022.
//

#include <stdexcept>
#include "VisitorUtils.h"

namespace cliargs {
    ConstraintVariant asVariant(const std::shared_ptr<Constraint> &constraint) {
        if(auto p = std::dynamic_pointer_cast<std::shared_ptr<Argument>>(constraint)){
            return *p;
        }

        if(auto p = std::dynamic_pointer_cast<std::shared_ptr<OneOf>>(constraint)){
            return *p;
        }

        if(auto p = std::dynamic_pointer_cast<std::shared_ptr<AnyOf>>(constraint)){
            return *p;
        }

        throw std::runtime_error("Invalid constraint type");
    }
} // cliargs