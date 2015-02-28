#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "includes.hpp"
#include "command_type.hpp"
#include "arithmetic_operations.hpp"

namespace hack {
    namespace utilities {
        void trim(std::string&);
        void stripComments(std::string&);
        bool isWhitespace(std::string&);
        std::string getShortFileName(const std::string&);
        std::string commandTypeAsString(const CommandType&);
        ArithmeticOperations arithmeticCommandToOperation(const std::string&);
        //std::vector<std::string> getVmFiles(const boost::filesystem::path&);
    }
}

#endif
