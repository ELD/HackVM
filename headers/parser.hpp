#ifndef _PARSER_H_
#define _PARSER_H_

#include "includes.hpp"

namespace hack {
    class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        Parser(Parser&&) = delete;
        Parser(const Parser&) = delete;
    private:
    };
}

#endif
