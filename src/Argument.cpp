//
// Created by renaud.rwemalika on 7/6/2022.
//

#include "cliargs/cliargs.h"
#include "Argument_p.h"
#include "ParserUtils.h"

namespace cliargs {
    inline Argument::Impl::Impl(Argument* interface,
                                  std::string flag,
                                  std::string name,
                                  std::string desc)
            : m_interface(interface),
              m_flag(std::move(flag)),
              m_name(std::move(name)),
              m_description(std::move(desc)) {

        if(!m_flag.empty()){
            if (m_flag.length() > 1){
                throw SpecificationException(
                        "Argument flag can only be one character long",
                        m_flag);
            }

            if (!std::isalpha(m_flag.at(0))){
                throw SpecificationException(
                        "When defined, flag of an argument must be an alphabetic character",
                        m_flag);
            }
        }
    }

    Argument::Argument(const std::string& flag, const std::string& name, const std::string& description){
        impl = std::make_unique<Argument::Impl>(this, flag, name, description);
    }

    Argument::Argument(const std::string &name, const std::string &description) {
        impl = std::make_unique<Argument::Impl>(this, "", name, description);
    }

    Argument::~Argument() = default;

    void Argument::setValueRequired(bool required) {
        impl->m_valueRequired = required;
    }

    void Argument::setAcceptMultipleValues(bool accept) {
        impl->m_acceptsMultipleValues = accept;
    }

    const std::string &cliargs::Argument::getFlag() const {
        return impl->m_flag;
    }

    const std::string &cliargs::Argument::getName() const {
        return impl->m_name;
    }

    std::string cliargs::Argument::getDescription() const {
        return impl->m_description;
    }

    bool cliargs::Argument::isValueRequired() const {
        return impl->m_valueRequired;
    }

    bool cliargs::Argument::isAcceptsMultipleValues() const{
        return impl->m_acceptsMultipleValues;
    }

    std::string cliargs::Argument::toString() const {
        std::string s;

        if (!impl->m_flag.empty()) s += getStartFlag() + impl->m_flag + " ";

        s += "(" + getStartName() + impl->m_name + ")";

        return s;
    }

    bool cliargs::Argument::operator==(const cliargs::Argument &a) const {
        return (!impl->m_flag.empty() && impl->m_flag == a.impl->m_flag)
               || impl->m_name == a.impl->m_name;
    }
} //namespace cliargs


