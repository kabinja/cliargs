//
// Created by renau on 8/17/2022.
//

#include "cliargs/cliargs.h"

namespace cliargs{
    class Constraint::Impl {
    public:
        bool m_required = false;
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
}//cliargs