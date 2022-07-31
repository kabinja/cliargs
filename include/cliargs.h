//
// Created by renaud.rwemalika on 7/6/2022.
//

#ifndef CLIARGS_CLIARGS_H
#define CLIARGS_CLIARGS_H

#include <list>
#include <string>
#include <vector>
#include <memory>

namespace cliargs{
    class Constraint {
    public:
        Constraint() = default;
        Constraint(const Constraint &) = delete;
        Constraint &operator=(const Constraint &) = delete;
        virtual ~Constraint() = default;

        [[nodiscard]] virtual bool isValid() const = 0;
        [[nodiscard]] virtual bool isRequired() const = 0;
        [[nodiscard]] virtual std::string toString() const = 0;
    };


    class Argument: public Constraint{
    public:
        Argument(const std::string& flag,
                 const std::string& name,
                 const std::string& description,
                 bool required = false,
                 bool valueRequired = true);
        Argument(const Argument &rhs) = delete;
        Argument &operator=(const Argument &rhs) = delete;
        ~Argument() override;

        [[nodiscard]] bool isValid() const override;
        [[nodiscard]] bool isRequired() const override;
        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] const std::string &getFlag() const;
        [[nodiscard]] const std::string &getName() const;
        [[nodiscard]] std::string getDescription() const;
        [[nodiscard]] std::string getDescription(bool required) const;
        [[nodiscard]] bool isValueRequired() const;
        [[nodiscard]] bool isSet() const;
        [[nodiscard]] const std::string &getSetBy() const;

        [[nodiscard]] static std::string getStartFlag();
        [[nodiscard]] static std::string getStartName();
        static void extractFlag(std::string &flag, std::string &value);

        virtual bool allowMore();
        virtual bool acceptsMultipleValues();
        virtual void reset();
        virtual void hideFromHelp(bool hide);
        [[nodiscard]] virtual bool visibleInHelp() const;
        [[nodiscard]] virtual bool hasLabel() const;
        [[nodiscard]] virtual bool matches(const std::string &argFlag) const;
        [[nodiscard]] virtual std::string getShortId(const std::string &valueId) const;
        [[nodiscard]] virtual std::string getLongId(const std::string &valueId) const;

        virtual bool operator==(const Argument &a) const;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };


    class GroupConstraint: public Constraint {
    public:
        GroupConstraint() = default;
        GroupConstraint(const GroupConstraint &) = delete;
        GroupConstraint &operator=(const GroupConstraint &) = delete;
        ~GroupConstraint() override = default;

        virtual GroupConstraint &add(std::unique_ptr<Constraint> constraint);

        [[nodiscard]] std::vector<std::unique_ptr<Constraint>>::iterator begin();
        [[nodiscard]] std::vector<std::unique_ptr<Constraint>>::iterator end();
        [[nodiscard]] std::vector<std::unique_ptr<Constraint>>::const_iterator begin() const;
        [[nodiscard]] std::vector<std::unique_ptr<Constraint>>::const_iterator end() const;

    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };


    class AnyOf: public GroupConstraint {
    public:
        AnyOf() = default;
        AnyOf(const AnyOf &) = delete;
        AnyOf &operator=(const AnyOf &) = delete;

        [[nodiscard]] bool isValid() const override;
        [[nodiscard]] virtual bool isRequired() const override {return true;};
        [[nodiscard]] virtual std::string toString() const {return std::string();};
    };


    class OneOf: public GroupConstraint {
    public:
        OneOf() = default;
        OneOf(const AnyOf &) = delete;
        OneOf &operator=(const AnyOf &) = delete;

        [[nodiscard]] bool isValid() const override;
        GroupConstraint &add(std::unique_ptr<Constraint> argument) override;
    };

    class ArgumentException : public std::exception {
    public:
        explicit ArgumentException(const std::string& error = "undefined exception",
                              const std::string& argumentId = "undefined",
                              const std::string& typeDescription = "Generic ArgException");

        ~ArgumentException() noexcept override = default;

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

        CommandLineInterface virtual &add(std::shared_ptr<Argument>) = 0;

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
        CommandLine &add(std::unique_ptr<Constraint> constraint);
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
