//
// Created by renaud.rwemalika on 7/29/2022.
//

#include <utility>

#include "cliargs.h"

namespace cliargs{
    class ArgumentException::Impl {
    public:
        std::string m_error;
        std::string m_argumentId;
        std::string m_typeDescription;

        Impl(std::string error, std::string argumentId, std::string typeDescription)
        : m_error(std::move(error)),
          m_argumentId(std::move(argumentId)),
          m_typeDescription(std::move(typeDescription)) {}
    };

    ArgumentException::ArgumentException(const std::string& error, const std::string& argumentId, const std::string& typeDescription)
    : std::exception() {
        impl = std::make_unique<ArgumentException::Impl>(error, argumentId, typeDescription);
    }

    const char *ArgumentException::what() const noexcept {
        static std::string ex;
        ex = impl->m_argumentId + " -- " + impl->m_error;
        return ex.c_str();
    }

    std::string ArgumentException::error() const {
        return impl->m_error;
    }

    std::string ArgumentException::argumentId() const {
        if (impl->m_argumentId == "undefined")
            return " ";
        else
            return ("Argument: " + impl->m_argumentId);
    }

    std::string ArgumentException::typeDescription() const {
        return impl->m_typeDescription;
    }

    ArgumentException::~ArgumentException() noexcept = default;

    SpecificationException::SpecificationException(const std::string &error, const std::string &argumentId)
    : ArgumentException(error, argumentId, std::string("Failure to build constraints specification")){}
} // cliargs