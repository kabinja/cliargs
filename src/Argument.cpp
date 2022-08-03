//
// Created by renaud.rwemalika on 7/6/2022.
//

#include <utility>

#include "cliargs.h"
#include "Argument_p.h"
#include "Visitor.h"

namespace cliargs {
    inline Argument::Impl::Impl(Argument* interface,
                                  std::string flag,
                                  std::string name,
                                  std::string desc,
                                  bool req,
                                  bool valueRequired)
            : m_interface(interface),
              m_flag(std::move(flag)),
              m_name(std::move(name)),
              m_description(std::move(desc)),
              m_required(req),
              m_requireLabel("required"),
              m_valueRequired(valueRequired),
              m_alreadySet(false),
              m_setBy(),
              m_ignorable(true),
              m_acceptsMultipleValues(false),
              m_visibleInHelp(true) {

        if (m_flag.length() > 1){
            throw(SpecificationException("Argument flag can only be one character long", m_interface->toString()));
        }

        if (m_flag == cliargs::Argument::getStartFlag() || m_flag == cliargs::Argument::getStartName() || m_flag == " "){
            throw(SpecificationException(
                    "Argument flag cannot be either '"
                        + cliargs::Argument::getStartFlag() + "' or '"
                        + cliargs::Argument::getStartName() + "' or a space.",
                    m_interface->toString()));
        }
    }

    Argument::Argument(const std::string& flag, const std::string& name, const std::string& description, bool required, bool valueRequired){
        impl = std::make_unique<Argument::Impl>(this, flag, name, description, required, valueRequired);
    }

    Argument::~Argument() = default;

    bool Argument::isValid() const {
        return true;
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
        return getDescription(impl->m_required);
    }

    std::string cliargs::Argument::getDescription(bool required) const {
        return (required ? "(" + impl->m_requireLabel + ") " : "") + impl->m_description;
    }

    bool cliargs::Argument::isValueRequired() const {
        return impl->m_valueRequired;
    }

    bool cliargs::Argument::isSet() const {
        return impl->m_alreadySet;
    }

    const std::string &cliargs::Argument::getSetBy() const {
        return impl->m_setBy;
    }

    inline std::string Argument::getStartFlag() {
        return "-";
    }

    inline std::string Argument::getStartName() {
        return "--";
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

    inline bool cliargs::Argument::allowMore() {
        return false;
    }

    bool cliargs::Argument::acceptsMultipleValues() {
        return impl->m_acceptsMultipleValues;
    }

    void cliargs::Argument::reset() {
        impl->m_alreadySet = false;
    }

    void cliargs::Argument::hideFromHelp(bool hide) {
        impl->m_visibleInHelp = !hide;
    }

    bool cliargs::Argument::visibleInHelp() const {
        return impl->m_visibleInHelp;
    }

    inline bool cliargs::Argument::hasLabel() const {
        return true;
    }

    bool cliargs::Argument::matches(const std::string &argFlag) const {
        return (argFlag == getStartFlag() + impl->m_flag && !impl->m_flag.empty())
            || argFlag == getStartName() + impl->m_name;
    }

    std::string cliargs::Argument::toString() const {
        std::string s;

        if (!impl->m_flag.empty()) s += getStartFlag() + impl->m_flag + " ";

        s += "(" + getStartName() + impl->m_name + ")";

        return s;
    }

    std::string cliargs::Argument::getShortId(const std::string &valueId) const {
        std::string id = impl->m_flag.empty() ? getStartName() + impl->m_name : getStartFlag() + impl->m_flag;

        if (impl->m_valueRequired){
            id += std::string(1, ' ') + valueId;
        }

        return id;
    }

    std::string cliargs::Argument::getLongId(const std::string &valueId) const {
        std::string id;

        if (!impl->m_flag.empty()) {
            id += getStartFlag() + impl->m_flag;

            if (impl->m_valueRequired){
                id += std::string(1, ' ') + valueId;
            }

            id += ",  ";
        }

        id += getStartName() + impl->m_name;

        if (impl->m_valueRequired) id += std::string(1, ' ') + valueId;

        return id;
    }

    bool cliargs::Argument::operator==(const cliargs::Argument &a) const {
        return (!impl->m_flag.empty() && impl->m_flag == a.impl->m_flag)
               || impl->m_name == a.impl->m_name;
    }

    void Argument::accept(Visitor *visitor) {
        visitor->visit(this);
    }
} //namespace cliargs


