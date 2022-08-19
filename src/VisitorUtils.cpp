//
// Created by renau on 8/1/2022.
//

#include "VisitorUtils.h"

namespace cliargs {
    ConstraintVariant asVariant(const std::shared_ptr<Constraint> &constraint) {
        if(auto p = std::dynamic_pointer_cast<Argument>(constraint)){
            return p;
        }

        if(auto p = std::dynamic_pointer_cast<OneOf>(constraint)){
            return p;
        }

        if(auto p = std::dynamic_pointer_cast<AnyOf>(constraint)){
            return p;
        }

        throw SpecificationException("Invalid constraint type");
    }

    void CollectArgumentsVisitor::operator()(const std::shared_ptr<Argument> &argument) {
        arguments.push_back(argument);
    }

    void CollectArgumentsVisitor::operator()(const std::shared_ptr<OneOf> &oneOf) {
        for(const auto& constraint: *oneOf){
            std::visit(*this, asVariant(constraint));
        }
    }

    void CollectArgumentsVisitor::operator()(const std::shared_ptr<AnyOf> &anyOf) {
        for(const auto& constraint: *anyOf){
            std::visit(*this, asVariant(constraint));
        }
    }

    std::vector<std::shared_ptr<Argument>>::const_iterator CollectArgumentsVisitor::begin() const {
        return arguments.cbegin();
    }

    std::vector<std::shared_ptr<Argument>>::const_iterator CollectArgumentsVisitor::end() const {
        return arguments.cend();
    }
} // cliargs