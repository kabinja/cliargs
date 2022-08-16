//
// Created by renaud.rwemalika on 7/6/2022.
//

#include "cliargs.h"
#include "VisitorUtils.h"

namespace cliargs{
    class UniqueNameVisitor{
    public:
        void operator()(const std::shared_ptr<Argument>& argument){
            arguments.push_back(argument);
        }

        void operator()(const std::shared_ptr<OneOf>& oneOf){
            for(const auto& constraint: *oneOf){
                std::visit(*this, asVariant(constraint));
            }
        }

        void operator()(const std::shared_ptr<AnyOf>& anyOf){
            for(const auto& constraint: *anyOf){
                std::visit(*this, asVariant(constraint));
            }
        }

    private:
        std::vector<std::shared_ptr<Argument>> arguments;
    };

    class UniqueName: public GroupConstraint {
    public:
        UniqueName() = default;
        UniqueName(const UniqueName &) = delete;
        UniqueName &operator=(const UniqueName &) = delete;

        [[nodiscard]] bool isValid() const override {
            UniqueNameVisitor visitor;

            for(const auto& constraint: *this){
                std::visit(visitor, asVariant(constraint));
            }
        }
    };


    class CommandLine::Impl {
    public:
        std::vector<std::shared_ptr<Argument>> m_autoArguments;
        std::vector<std::unique_ptr<Constraint>> m_constraints;


        std::string m_progName;
        std::string m_message;
        std::string m_version;
        int m_minimumNumberArguments;
        char m_delimiter;
        CommandLineOutput *m_output;
        bool m_handleExceptions;

        void parse(std::vector<std::string> &args);
    };

    CommandLine &CommandLine::add(std::unique_ptr<Constraint> constraint) {
        impl->m_constraints.push_back(std::move(constraint));
        return *this;
    }

    void CommandLine::parse(int argc, const char *const *argv) {
        std::vector<std::string> args(argc);
        for (int i = 0; i < argc; i++) args.emplace_back(argv[i]);
        impl->parse(args);
    }

    void CommandLine::setOutput(CommandLineOutput *co) {

    }

    std::string CommandLine::getVersion() const {
        return {};
    }

    std::string CommandLine::getProgramName() const {
        return {};
    }

    std::string CommandLine::getMessage() const {
        return {};
    }

    bool CommandLine::hasHelpAndVersion() const {
        return false;
    }

    void CommandLine::reset() {

    }

    void CommandLine::Impl::parse(std::vector<std::string> &args) {

    }
} // cliargs