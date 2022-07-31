//
// Created by renaud.rwemalika on 7/28/2022.
//

#include "cliargs.h"

namespace cliargs {

    class GroupConstraint::Impl {
    public:
        std::vector<std::unique_ptr<Constraint>> constraints;
    };

    GroupConstraint &GroupConstraint::add(std::unique_ptr<Constraint> constraint) {
        impl->constraints.push_back(std::move(constraint));
        return *this;
    }

    std::vector<std::unique_ptr<Constraint>>::iterator GroupConstraint::begin() {
        return impl->constraints.begin();
    }

    std::vector<std::unique_ptr<Constraint>>::iterator GroupConstraint::end() {
        return impl->constraints.end();
    }

    std::vector<std::unique_ptr<Constraint>>::const_iterator GroupConstraint::begin() const {
        return impl->constraints.cbegin();
    }

    std::vector<std::unique_ptr<Constraint>>::const_iterator GroupConstraint::end() const {
        return impl->constraints.cend();
    }

} // namespace cliargs