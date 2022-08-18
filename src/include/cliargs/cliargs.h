//
// Created by renaud.rwemalika on 7/6/2022.
//

#ifndef CLIARGS_CLIARGS_H
#define CLIARGS_CLIARGS_H

#include <list>
#include <string>
#include <vector>
#include <memory>
#include <variant>

namespace cliargs{
    class Constraint {
    public:
        Constraint();
        Constraint(const Constraint &) = delete;
        Constraint &operator=(const Constraint &) = delete;
        virtual ~Constraint();

        void setRequired(bool required);
        [[nodiscard]] bool isRequired() const;

        [[nodiscard]] virtual std::string toString() const = 0;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };

    class Argument: public Constraint{
    public:
        Argument(const std::string& flag,
                 const std::string& name,
                 const std::string& description);
        Argument(const Argument &rhs) = delete;
        Argument &operator=(const Argument &rhs) = delete;
        ~Argument() override;

        void setValueRequired(bool required);
        void setAcceptMultipleValues(bool accept);

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] const std::string &getFlag() const;
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] std::string getDescription() const;
        [[nodiscard]] bool isValueRequired() const;
        [[nodiscard]] bool isAcceptsMultipleValues() const;

        virtual bool operator==(const Argument &a) const;
    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };


    class GroupConstraint: public Constraint {
    public:
        GroupConstraint();
        GroupConstraint(const GroupConstraint &) = delete;
        GroupConstraint &operator=(const GroupConstraint &) = delete;
        ~GroupConstraint() override;

        virtual GroupConstraint &add(std::unique_ptr<Constraint> constraint);

        [[nodiscard]] std::vector<std::shared_ptr<Constraint>>::const_iterator begin() const;
        [[nodiscard]] std::vector<std::shared_ptr<Constraint>>::const_iterator end() const;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };


    class AnyOf: public GroupConstraint {
    public:
        AnyOf() = default;
        AnyOf(const AnyOf &) = delete;
        AnyOf &operator=(const AnyOf &) = delete;

        [[nodiscard]] std::string toString() const override;
    };


    class OneOf: public GroupConstraint {
    public:
        OneOf() = default;
        OneOf(const AnyOf &) = delete;
        OneOf &operator=(const AnyOf &) = delete;

        [[nodiscard]] std::string toString() const override;

        GroupConstraint &add(std::unique_ptr<Constraint> argument) override;
    };

    using ConstraintVariant = std::variant<std::shared_ptr<Argument>, std::shared_ptr<AnyOf>, std::shared_ptr<OneOf>>;

    class ArgumentException : public std::exception {
    public:
        explicit ArgumentException(const std::string& error = "undefined exception",
                              const std::string& argumentId = "undefined",
                              const std::string& typeDescription = "Generic ArgException");

        ~ArgumentException() noexcept override;

        [[nodiscard]] const char *what() const noexcept override;

        [[nodiscard]] std::string error() const;
        [[nodiscard]] std::string argumentId() const;
        [[nodiscard]] std::string typeDescription() const;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };


    class SpecificationException : public ArgumentException {
    public:
        explicit SpecificationException(const std::string &error = "undefined exception",
                                        const std::string &argumentId = "undefined");
    };

    class CommandLineOutput;
    class CommandLineInterface {
    public:
        ~CommandLineInterface() = default;

        virtual void add(std::shared_ptr<Constraint>) = 0;
        virtual void parse(int argc, const char *const *argv) = 0;
        virtual void setOutput(CommandLineOutput *co) = 0;
        virtual void reset() = 0;
        [[nodiscard]] virtual std::string getVersion() const = 0;
        [[nodiscard]] virtual std::string getProgramName() const = 0;
        [[nodiscard]] virtual std::string getMessage() const = 0;
        [[nodiscard]] virtual bool hasHelpAndVersion() const = 0;
    };


    class CommandLineOutput {
    public:
        virtual ~CommandLineOutput() = default;

        virtual void usage(CommandLineInterface &c) = 0;
        virtual void version(CommandLineInterface &c) = 0;
        virtual void failure(CommandLineInterface &c, ArgumentException &e) = 0;
    };

    class CommandLine: public CommandLineInterface{
    public:
        CommandLine();
        CommandLine(const AnyOf &) = delete;
        CommandLine(const CommandLine &) = delete;
        CommandLine &operator=(const CommandLine &) = delete;
        ~CommandLine();

        void add(std::shared_ptr<Constraint> constraint) override;
        void parse(int argc, const char *const *argv) override;
        void setOutput(CommandLineOutput *co) override;
        [[nodiscard]] std::string getVersion() const override;
        [[nodiscard]] std::string getProgramName() const override;
        [[nodiscard]] std::string getMessage() const override;
        [[nodiscard]] bool hasHelpAndVersion() const override;
        void reset() override;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };
}

#endif //CLIARGS_CLIARGS_H
