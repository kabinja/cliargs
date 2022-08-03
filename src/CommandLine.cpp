//
// Created by renaud.rwemalika on 7/6/2022.
//

#include "cliargs.h"
#include "VisitorUtils.h"
#include "Visitor.h"

namespace cliargs{
    class UniqueNameVisitor: public Visitor{
    public:
        void visit(const Argument* argument) override{
            arguments.push_back(argument);
        }

        void visit(const AnyOf* anyOf) override{
            VisitorUtils::traverse(this, anyOf);
        }

        void visit(const OneOf* oneOf) override{
            VisitorUtils::traverse(this, oneOf);
        }

    private:
        std::vector<const Argument*> arguments;
    };

    class UniqueName: public GroupConstraint {
    public:
        UniqueName() = default;
        UniqueName(const UniqueName &) = delete;
        UniqueName &operator=(const UniqueName &) = delete;

        [[nodiscard]] bool isValid() const override {
            UniqueNameVisitor visitor;
            VisitorUtils::traverse(&visitor, this);
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

    void CommandLine::Impl::parse(std::vector<std::string> &args) {

    }
} // cliargs