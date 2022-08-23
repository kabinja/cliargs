//
// Created by renau on 8/18/2022.
//

#include "Parser.h"

#include <utility>
#include "cliargs/cliargs.h"
#include "VisitorUtils.h"

namespace cliargs {
    class MatchVisitor: public Visitor {
    public:
        explicit MatchVisitor(const std::string &flag, const std::string &label)
        :m_flag(flag), m_label(label) {}

        void operator()(const std::shared_ptr<Argument>& argument) override {
            if(m_flag == Parser::getStartFlag() && argument->getName() == m_label){
                m_matching = argument;
            }
            else if(m_flag == Parser::getStartName() && argument->getFlag() == m_label){
                m_matching = argument;
            }
        }

        void operator()(const std::shared_ptr<OneOf>& oneOf) override {
            for(const auto& constraint: *oneOf){
                if(m_matching) break;
                std::visit(*this, asVariant(constraint));
            }
        }

        void operator()(const std::shared_ptr<AnyOf>& anyOf) override {
            for(const auto& constraint: *anyOf){
                if(m_matching) break;
                std::visit(*this, asVariant(constraint));
            }
        }

        std::shared_ptr<Argument> getMatch(){
            return m_matching;
        }

    private:
        std::shared_ptr<Argument> m_matching;
        const std::string &m_flag;
        const std::string &m_label;
    };

    Parser::Parser(std::shared_ptr<OneOf> root, std::vector<std::string> args)
            : m_root(std::move(root)), m_args(std::move(args)){}

    void Parser::parse() {
        if(m_args.empty()){
            throw ParserException("The command should have at least one implicit argument containing the name of the program.");
        }

        int argumentPosition = 1;

        while (argumentPosition < m_args.size()){
            const std::string &current = m_args[argumentPosition];
            if(isLabel(current)){
                argumentPosition = parseArgument(current, argumentPosition);
            } else{
                throw ParserException("Expected a label (starting with '-' or '--'", current);
            }
        }
    }

    std::string Parser::getStartFlag() {
        return "-";
    }

    std::string Parser::getStartName() {
        return "--";
    }

    bool Parser::isLabel(const std::string& token){
        return token.rfind(getStartFlag(), 0) != std::string::npos
               || token.rfind(getStartName(), 0) != std::string::npos;
    }

    int Parser::parseArgument(const std::string &argumentLabel, int start) {
        std::shared_ptr<Argument> argument = matches(argumentLabel);
        return start;
    }

    std::shared_ptr<Argument> Parser::matches(const std::string &argument) const{
        std::string flag;
        std::string label;
        splitLabel(argument, flag, label);

        MatchVisitor visitor(flag, label);
        std::visit(visitor, asVariant(m_root));

        return visitor.getMatch();
    }

    void Parser::splitLabel(const std::string &argument, std::string &flag, std::string &label) {
        auto pos1 = argument.rfind(getStartFlag(), 0);
        auto pos2 = argument.rfind(getStartName(), 0);
        auto position = std::max(pos1, pos2);

        flag = argument.substr(0, position);
        label = argument.substr(position);
    }

} //namespace cliargs

