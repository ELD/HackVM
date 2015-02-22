#include "../headers/utilities.hpp"

namespace hack {
    namespace utilities {
        void trim(std::string& commandToTrim)
        {
            if (commandToTrim.size() > 0) {
                auto firstPos = commandToTrim.find_first_not_of(' ');
                auto lastPos = commandToTrim.find_last_not_of(' ');
                commandToTrim = commandToTrim.substr(firstPos, (lastPos - firstPos + 1));

                commandToTrim.erase(std::remove(commandToTrim.begin(), commandToTrim.end(), '\r'), commandToTrim.end());
                commandToTrim.erase(std::remove(commandToTrim.begin(), commandToTrim.end(), '\t'), commandToTrim.end());
            }
        }

        void stripComments(std::string& commandToTrim)
        {
            auto commentPos = commandToTrim.find_first_of("//");
            if (commentPos != std::string::npos) {
                commandToTrim = commandToTrim.substr(0, commentPos);
            }
        }

        bool isWhitespace(std::string& line)
        {
            for (char c : line) {
                if (!std::isspace(c)) {
                    return false;
                }
            }

            return true;
        }

        std::string commandTypeAsString(const CommandType& command)
        {
            std::string retVal;

            switch (command) {
                case CommandType::C_ARITHMETIC:
                    retVal = "C_ARITHMETIC";
                    break;
                case CommandType::C_PUSH:
                    retVal = "C_PUSH";
                    break;
                case CommandType::C_POP:
                    retVal = "C_POP";
                    break;
                case CommandType::C_LABEL:
                    retVal = "C_LABEL";
                    break;
                case CommandType::C_GOTO:
                    retVal = "C_GOTO";
                    break;
                case CommandType::C_IF:
                    retVal = "C_IF";
                    break;
                case CommandType::C_FUNCTION:
                    retVal = "C_FUNCTION";
                    break;
                case CommandType::C_RETURN:
                    retVal = "C_RETURN";
                    break;
                case CommandType::C_CALL:
                    retVal = "C_CALL";
                    break;
                default:
                    retVal = "";
            }

            return retVal;
        }
    }
}
