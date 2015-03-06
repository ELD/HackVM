#include "../headers/parser.hpp"
#include "../headers/utilities.hpp"

namespace hack {

    Parser::Parser(std::istream& inputStream) : _file(inputStream)
    {
        _currentCommand = "";
        _argRegex = R"(^(?:[\w-]+)\s([\w]+)(?:\s([\d]+))*\s*$)";
    }

    bool Parser::hasMoreCommands()
    {
        std::string tempLine;
        auto position = _file.tellg();
        getline(_file, tempLine);
        _file.seekg(position);
        if (tempLine == "" || _file.eof()) {
            _file.seekg(position);
            return false;
        } else {
            return true;
        }
    }

    void Parser::advance()
    {
        std::string tempCommand;
        do {
            getline(_file, tempCommand);
            utilities::trim(tempCommand);
            utilities::stripComments(tempCommand);
        } while ((utilities::isWhitespace(tempCommand) || tempCommand.substr(0,2) == "//") && hasMoreCommands());

        _currentCommand = tempCommand;
    }

    std::string Parser::getCurrentCommand()
    {
        return _currentCommand;
    }

    CommandType Parser::commandType()
    {
        std::regex pushRegex(R"(^push\s.*)");
        std::regex popRegex(R"(^pop\s.*)");
        std::regex arithmeticRegex(R"(^add|sub|neg|eq|lt|gt|and|or|not)");
        std::regex labelRegex(R"(^label\s*(?:\w*))");
        std::regex gotoRegex(R"(^goto\s*(?:\w*))");
        std::regex ifGotoRegex(R"(^if-goto\s*(?:\w*))");
        std::regex functionRegex(R"(^function\s*(?:\w*)\s*(?:\d*))");
        std::regex returnRegex(R"(^return)");
        std::regex callRegex(R"(^call\s*(?:\w*)\s*(?:\d*))");

        if (std::regex_search(_currentCommand, pushRegex)) {
            return CommandType::C_PUSH;
        } else if (std::regex_search(_currentCommand, popRegex)) {
            return CommandType::C_POP;
        } else if (std::regex_search(_currentCommand, arithmeticRegex)) {
            return CommandType::C_ARITHMETIC;
        } else if (std::regex_search(_currentCommand, labelRegex)) {
            return CommandType::C_LABEL;
        } else if (std::regex_search(_currentCommand, gotoRegex)) {
            return CommandType::C_GOTO;
        } else if (std::regex_search(_currentCommand, ifGotoRegex)) {
            return CommandType::C_IF;
        } else if (std::regex_search(_currentCommand, functionRegex)) {
            return CommandType::C_FUNCTION;
        } else if (std::regex_search(_currentCommand, returnRegex)) {
            return CommandType::C_RETURN;
        } else if (std::regex_search(_currentCommand, callRegex)) {
            return CommandType::C_CALL;
        }

        return CommandType::C_PUSH;
    }

    std::string Parser::arg1()
    {
        std::sregex_token_iterator p{_currentCommand.begin(), _currentCommand.end(), _argRegex, 1};
        return *p;
    }

    int Parser::arg2()
    {
        int arg2AsInt = -1;
        std::sregex_token_iterator p{_currentCommand.begin(), _currentCommand.end(), _argRegex, 2};
        try {
            arg2AsInt = std::stoi(*p);
        } catch (std::invalid_argument exc) {
            arg2AsInt = -1;
        }
        return arg2AsInt;
    }
}
