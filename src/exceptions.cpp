//
// Created by renaud.rwemalika on 7/29/2022.
//

#include <utility>

#include "cliargs/cliargs.h"

namespace cliargs{
    class CliException::Impl {
    public:
        std::string m_error;
        std::string m_argumentId;
        std::string m_typeDescription;

        Impl(std::string error, std::string argumentId, std::string typeDescription)
        : m_error(std::move(error)),
          m_argumentId(std::move(argumentId)),
          m_typeDescription(std::move(typeDescription)) {}
    };

    CliException::CliException(const std::string& error, const std::string& argumentId, const std::string& typeDescription)
    : std::exception() {
        impl = std::make_unique<CliException::Impl>(error, argumentId, typeDescription);
    }

    const char *CliException::what() const noexcept {
        static std::string ex;
        ex = impl->m_argumentId + " -- " + impl->m_error;
        return ex.c_str();
    }

    std::string CliException::error() const {
        return impl->m_error;
    }

    std::string CliException::argumentId() const {
        if (impl->m_argumentId == "undefined")
            return " ";
        else
            return ("Argument: " + impl->m_argumentId);
    }

    std::string CliException::typeDescription() const {
        return impl->m_typeDescription;
    }

    CliException::~CliException() noexcept = default;

    SpecificationException::SpecificationException(const std::string &error, const std::string &argumentId)
    : CliException(error, argumentId, std::string("Failure to build constraints specification")){}

    ParserException::ParserException(const std::string &error, const std::string &argumentId)
    : CliException(error, argumentId, std::string("Failure to parse arguments")){}
} // cliargs