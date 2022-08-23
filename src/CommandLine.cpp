//
// Created by renaud.rwemalika on 7/6/2022.
//

#include <utility>

#include "cliargs/cliargs.h"
#include "validators.h"
#include "Parser.h"

namespace cliargs{
    class CommandLine::Impl {
    public:
        std::shared_ptr<OneOf> m_root = std::make_shared<OneOf>();
        std::string m_name;
        std::string m_message;
        std::string m_version;
        std::string m_executable;
        std::shared_ptr<CommandLineOutput> m_output = nullptr;

        Impl() {
            m_root->add(std::make_unique<AnyOf>());
        }

        void add(std::unique_ptr<Constraint> constraint){
            std::static_pointer_cast<AnyOf>(*m_root->begin())->add(std::move(constraint));
        }
    };

    CommandLine::CommandLine() {
        impl = std::make_unique<CommandLine::Impl>();
    }

    CommandLine::~CommandLine() = default;

    void CommandLine::add(std::unique_ptr<Constraint> constraint) {
        impl->add(std::move(constraint));
    }

    void CommandLine::parse(int argc, const char *const *argv) {
        std::vector<std::string> args(argc);
        for (int i = 0; i < argc; i++) args.emplace_back(argv[i]);

        Parser parser(impl->m_root, args);
        parser.parse();
    }

    void CommandLine::setOutput(std::shared_ptr<CommandLineOutput> output) {
        impl->m_output = std::move(output);
    }

    std::string CommandLine::getVersion() const {
        return impl->m_version;
    }

    std::string CommandLine::getName() const {
        return impl->m_name;
    }

    std::string CommandLine::getMessage() const {
        return impl->m_message;
    }

    bool CommandLine::hasVersion() const {
        return !impl->m_version.empty();
    }

    void CommandLine::validate() const {
        std::vector<std::unique_ptr<validators>> validators;
        validators.push_back(std::make_unique<UniqueName>(impl->m_root));

        for(const auto& validator: validators){
            validator->validate();
        }
    }

    void CommandLine::reset() {

    }
} // cliargs