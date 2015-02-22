#ifndef _COMMAND_TYPES_H_
#define _COMMAND_TYPES_H_

namespace hack {

    enum class CommandType {
        C_ARITHMETIC = 0,
        C_PUSH,
        C_POP,
        C_LABEL,
        C_GOTO,
        C_IF,
        C_FUNCTION,
        C_RETURN,
        C_CALL
    };
}

#endif
