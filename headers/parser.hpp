#ifndef _PARSER_H_
#define _PARSER_H_

#include "includes.hpp"
#include "command_type.hpp"

namespace hack {
    class Parser {
    public:
        Parser() = default;
        Parser(std::istream&);
        ~Parser() = default;
        Parser(Parser&&) = delete;
        Parser(const Parser&) = delete;

        bool hasMoreCommands();
        void advance();
        CommandType commandType();
        std::string arg1();
        int arg2();

        std::string getCurrentCommand();
    private:
        std::istream& _file;
        std::string _currentCommand;
        std::regex _argRegex;
    };
}

#endif
