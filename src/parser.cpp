#include "../headers/parser.hpp"
#include "../headers/utilities.hpp"

namespace hack {

    Parser::Parser(std::istream& inputStream) : _file(inputStream)
    {
        _currentCommand = "";
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
        std::regex pushRegex(R"(push\s.*)");
        std::regex popRegex(R"(pop\s.*)");
        std::regex arithmeticRegex(R"(add|sub|neg|eq|lt|gt|and|or|not)");

        if (std::regex_search(_currentCommand, pushRegex)) {
            return CommandType::C_PUSH;
        } else if (std::regex_search(_currentCommand, popRegex)) {
            return CommandType::C_POP;
        } else if (std::regex_search(_currentCommand, arithmeticRegex)) {
            return CommandType::C_ARITHMETIC;
        }

        return CommandType::C_PUSH;
    }

    std::string Parser::arg1()
    {
        std::regex arg1{R"((?:push|pop)\s(\w*)\s[\d|\w]*)"};

        std::sregex_token_iterator p{_currentCommand.begin(), _currentCommand.end(), arg1, 1};
        return *p;
    }

    int Parser::arg2()
    {
        int arg2AsInt = -1;
        std::regex arg2{R"((?:push|pop)\s\w*\s([\w]*))"};

        std::sregex_token_iterator p{_currentCommand.begin(), _currentCommand.end(), arg2, 1};
        try {
            arg2AsInt = std::stoi(*p);
        } catch (std::invalid_argument exc) {
            // Do nothing
        }
        return arg2AsInt;
    }
}
