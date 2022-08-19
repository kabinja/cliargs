//
// Created by renau on 8/1/2022.
//

#ifndef CLIARGS_VISITORUTILS_H
#define CLIARGS_VISITORUTILS_H

#include "cliargs/cliargs.h"

namespace cliargs {
    [[nodiscard]] ConstraintVariant asVariant(const std::shared_ptr<Constraint>& constraint);

    class CollectArgumentsVisitor {
    public:
        void operator()(const std::shared_ptr<Argument>& argument);
        void operator()(const std::shared_ptr<OneOf>& oneOf);
        void operator()(const std::shared_ptr<AnyOf>& anyOf);

        [[nodiscard]] std::vector<std::shared_ptr<Argument>>::const_iterator begin() const;
        [[nodiscard]] std::vector<std::shared_ptr<Argument>>::const_iterator end() const;
    private:
        std::vector<std::shared_ptr<Argument>> arguments;
    };

} // cliargs

#endif //CLIARGS_VISITORUTILS_H
