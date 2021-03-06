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

        std::string getShortFileName(const std::string& file)
        {
            boost::filesystem::path filePath{file};
            if (boost::filesystem::is_regular_file(filePath)) {
                std::string intermediate = file.substr(file.find_last_of('/')+1);
                return intermediate.substr(0,intermediate.find_last_of('.'));
            }
            // Is a directory

            std::string intermediate = file;
            auto index1 = file.find_last_of('/');
            if (index1 + 1 == file.size()) {
                intermediate = file.substr(0, index1);
            }

            return intermediate.substr(intermediate.find_last_of('/') + 1);
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

        ArithmeticOperations arithmeticCommandToOperation(const std::string& arg1)
        {
            if (arg1 == "add") {
                return ArithmeticOperations::ADD;
            } else if (arg1 == "sub") {
                return ArithmeticOperations::SUB;
            } else if (arg1 == "and") {
                return ArithmeticOperations::AND;
            } else if (arg1 == "or") {
                return ArithmeticOperations::OR;
            } else if (arg1 == "neg") {
                return ArithmeticOperations::NEG;
            } else if (arg1 == "not") {
                return ArithmeticOperations::NOT;
            } else if (arg1 == "eq") {
                return ArithmeticOperations::EQ;
            } else if (arg1 == "lt") {
                return ArithmeticOperations::LT;
            } else {
                return ArithmeticOperations::GT;
            }
        }

        std::vector<std::string> getVmFiles(const boost::filesystem::path& dirToSearch)
        {
            std::vector<std::string> files;

            for (const auto& file : boost::make_iterator_range(boost::filesystem::recursive_directory_iterator{dirToSearch}, {})) {
                std::regex vmFile{R"((?:.*).vm)"};
                if (boost::filesystem::is_regular_file(file) && std::regex_search(file.path().string().begin(), file.path().string().end(), vmFile)) {
                    files.emplace_back(file.path().string());
                }
            }

            return files;
        }
    }
}
