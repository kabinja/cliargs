//
// Created by renau on 8/18/2022.
//

#include "ParserUtils.h"

namespace cliargs {
    void extractFlag(std::string &flag, std::string &value) {
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

    std::string getStartFlag() {
        return "-";
    }

    std::string getStartName() {
        return "--";
    }
} // cliargs