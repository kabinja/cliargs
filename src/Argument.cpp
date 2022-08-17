//
// Created by renaud.rwemalika on 7/6/2022.
//

#include <utility>

#include "cliargs/cliargs.h"
#include "Argument_p.h"

namespace cliargs {
    inline Argument::Impl::Impl(Argument* interface,
                                  std::string flag,
                                  std::string name,
                                  std::string desc)
            : m_interface(interface),
              m_flag(std::move(flag)),
              m_name(std::move(name)),
              m_description(std::move(desc)),
              m_required(true),
              m_requireLabel("required"),
              m_valueRequired(true),
              m_acceptsMultipleValues(false) {

        if (m_flag.length() > 1){
            throw(SpecificationException("Argument flag can only be one character long", m_interface->toString()));
        }

        if (m_flag == getStartFlag() || m_flag == getStartName() || m_flag == " "){
            throw(SpecificationException(
                    "Argument flag cannot be either '"
                        + getStartFlag() + "' or '"
                        + getStartName() + "' or a space.",
                    m_interface->toString()));
        }
    }

    Argument::Argument(const std::string& flag, const std::string& name, const std::string& description){
        impl = std::make_unique<Argument::Impl>(this, flag, name, description);
    }

    Argument::~Argument() = default;

    Argument &Argument::setRequired(bool required) {
        impl->m_required = required;
        return *this;
    }

    Argument &Argument::setValueRequired(bool required) {
        impl->m_valueRequired = required;
        return *this;
    }

    Argument &Argument::setAcceptMultipleValues(bool accept) {
        impl->m_acceptsMultipleValues = accept;
        return *this;
    }

    bool cliargs::Argument::isRequired() const {
        return impl->m_required;
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

    inline void cliargs::Argument::extractFlag(std::string &flag, std::string &value) {
        int stop = 0;

        for (int i = 0; static_cast<unsigned int>(i) < flag.length(); i++){
            if (std::isspace(flag[i])) {
                stop = i;
                break;
            }
        }

        if (stop > 1) {
            value = flag.substr(stop + 1);
            flag = flag.substr(0, stop);
        }
    }

    inline std::string cliargs::Argument::getStartFlag() {
        return "-";
    }

    inline std::string cliargs::Argument::getStartName() {
        return "--";
    }
} //namespace cliargs


