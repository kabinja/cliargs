//
// Created by renau on 8/1/2022.
//

#ifndef CLIARGS_VISITORUTILS_H
#define CLIARGS_VISITORUTILS_H

#include "cliargs/cliargs.h"

namespace cliargs {
    [[nodiscard]] ConstraintVariant asVariant(const std::shared_ptr<Constraint>& constraint);
} // cliargs

#endif //CLIARGS_VISITORUTILS_H
