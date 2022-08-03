//
// Created by renau on 8/1/2022.
//

#ifndef CLIARGS_VISITOR_H
#define CLIARGS_VISITOR_H

#include "cliargs.h"

namespace cliargs{
    class Visitor {
    public:
        Visitor() = default;
        virtual ~Visitor() = default;

        virtual void visit(const Argument* argument) = 0;
        virtual void visit(const AnyOf* anyOf) = 0;
        virtual void visit(const OneOf* oneOf) = 0;
    };
}

#endif //CLIARGS_VISITOR_H
