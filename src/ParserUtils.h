//
// Created by renau on 8/18/2022.
//

#ifndef CLIARGS_PARSERUTILS_H
#define CLIARGS_PARSERUTILS_H

#include <string>

namespace cliargs {
    void extractFlag(std::string &flag, std::string &value);
    [[nodiscard]] std::string getStartFlag();
    [[nodiscard]] std::string getStartName();
} // cliargs

#endif //CLIARGS_PARSERUTILS_H
