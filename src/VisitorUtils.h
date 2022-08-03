//
// Created by renau on 8/1/2022.
//

#ifndef CLIARGS_VISITORUTILS_H
#define CLIARGS_VISITORUTILS_H

#include "cliargs.h"

namespace cliargs {

    class VisitorUtils {
    public:
        static void traverse(Visitor* visitor, const GroupConstraint *groupConstraint);
    };

} // cliargs

#endif //CLIARGS_VISITORUTILS_H
