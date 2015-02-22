#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "includes.hpp"
#include "command_type.hpp"

namespace hack {
    namespace utilities {
        void trim(std::string&);
        void stripComments(std::string&);
        bool isWhitespace(std::string&);
        std::string commandTypeAsString(const CommandType&);
    }
}

#endif
