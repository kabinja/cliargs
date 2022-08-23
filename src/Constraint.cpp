//
// Created by renau on 8/17/2022.
//

#include "cliargs/cliargs.h"

namespace cliargs{
    class Constraint::Impl {
    public:
        bool m_required = false;
        const Constraint* m_parent = nullptr;
    };

    Constraint::Constraint() {
        impl = std::make_unique<Constraint::Impl>();
    }

    Constraint::~Constraint() = default;

    void Constraint::setRequired(bool required) {
        impl->m_required = required;
    }

    bool Constraint::isRequired() const {
        return impl->m_required;
    }

    void Constraint::setParent(const Constraint* constraint) {
        impl->m_parent = constraint;
    }

    const Constraint* Constraint::getParent() {
        return impl->m_parent;
    }
}//cliargs