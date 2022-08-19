//
// Created by renau on 8/19/2022.
//

#ifndef CLIARGS_VALIDATOR_H
#define CLIARGS_VALIDATOR_H

#include "cliargs/cliargs.h"

namespace cliargs {
    class validators {
    public:
        virtual ~validators() = default;
        virtual void validate() = 0;
    };

    class UniqueName: public validators {
    public:
        explicit UniqueName(std::shared_ptr<OneOf> root);
        UniqueName(const UniqueName &) = delete;
        UniqueName &operator=(const UniqueName &) = delete;

        void validate() override;

    private:
        std::shared_ptr<OneOf> m_root;
    };
}

#endif //CLIARGS_VALIDATOR_H