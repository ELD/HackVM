#include "../headers/parser.hpp"

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
}
