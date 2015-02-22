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
    }
}
