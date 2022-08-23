//
// Created by renau on 8/18/2022.
//

#ifndef CLIARGS_PARSER_H
#define CLIARGS_PARSER_H

#include <string>
#include <vector>
#include "cliargs/cliargs.h"

namespace cliargs {
    class Parser{
    public:
        explicit Parser(std::shared_ptr<OneOf> root, std::vector<std::string> args);

        void parse();

        [[nodiscard]] static std::string getStartFlag();
        [[nodiscard]] static std::string getStartName();
        [[nodiscard]] static bool isLabel(const std::string &token);
        static void splitLabel(const std::string &argument, std::string &prefix, std::string &label);
    private:
        std::shared_ptr<OneOf> m_root;
        std::vector<std::string> m_args;

        [[nodiscard]] int parseArgument(const std::string &label, int start);
        [[nodiscard]] std::shared_ptr<Argument> matches(const std::string &label) const;
    };
} // cliargs

#endif //CLIARGS_PARSER_H
