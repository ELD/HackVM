#include "../headers/parser.hpp"
#include "../headers/utilities.hpp"

namespace hack {

    Parser::Parser(std::istream& inputStream) : _file(inputStream)
    {
        // TODO: Add more things to the parser, etc
        _currentCommand = "";
    }

    bool Parser::hasMoreCommands()
    {
        return !_file.eof();
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
}
