//
// Created by renaud.rwemalika on 7/28/2022.
//

#include "cliargs/cliargs.h"

namespace cliargs {

    class GroupConstraint::Impl {
    public:
        std::vector<std::shared_ptr<Constraint>> constraints;
    };

    GroupConstraint::GroupConstraint() {
        impl = std::make_unique<GroupConstraint::Impl>();
    }

    GroupConstraint::~GroupConstraint() = default;

    GroupConstraint &GroupConstraint::add(std::unique_ptr<Constraint> constraint) {
        constraint->setParent(this);
        impl->constraints.push_back(std::move(constraint));
        return *this;
    }

    std::vector<std::shared_ptr<Constraint>>::const_iterator GroupConstraint::begin() const {
        return impl->constraints.cbegin();
    }

    std::vector<std::shared_ptr<Constraint>>::const_iterator GroupConstraint::end() const {
        return impl->constraints.cend();
    }
} // namespace cliargs