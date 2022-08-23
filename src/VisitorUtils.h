//
// Created by renau on 8/1/2022.
//

#ifndef CLIARGS_VISITORUTILS_H
#define CLIARGS_VISITORUTILS_H

#include "cliargs/cliargs.h"

namespace cliargs {
    [[nodiscard]] ConstraintVariant asVariant(const std::shared_ptr<Constraint>& constraint);

    class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void operator()(const std::shared_ptr<Argument>& argument) = 0;
        virtual void operator()(const std::shared_ptr<OneOf>& oneOf) = 0;
        virtual void operator()(const std::shared_ptr<AnyOf>& anyOf) = 0;
    };

    class CollectArgumentsVisitor: public Visitor{
    public:
        void operator()(const std::shared_ptr<Argument>& argument) override;
        void operator()(const std::shared_ptr<OneOf>& oneOf) override;
        void operator()(const std::shared_ptr<AnyOf>& anyOf) override;

        [[nodiscard]] std::vector<std::shared_ptr<Argument>>::const_iterator begin() const;
        [[nodiscard]] std::vector<std::shared_ptr<Argument>>::const_iterator end() const;
    private:
        std::vector<std::shared_ptr<Argument>> arguments;
    };

} // cliargs

#endif //CLIARGS_VISITORUTILS_H
