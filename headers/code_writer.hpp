#ifndef _CODE_WRITER_H_
#define _CODE_WRITER_H_

#include "includes.hpp"
#include "../headers/arithmetic_operations.hpp"
#include "../headers/command_type.hpp"

namespace hack {

    class CodeWriter {
    public:
        CodeWriter() = default;
        CodeWriter(std::ostream&);
        ~CodeWriter() = default;
        CodeWriter(const CodeWriter&) = delete;
        CodeWriter(CodeWriter&&) = delete;
        void setFileName(const std::string&);
        void writeArithmetic(ArithmeticOperations&);
        void writePushPop(CommandType&, const std::string&, int);

        std::string getFileName() const;
        std::string getSymbolName() const;
    private:
        void writePush(const std::string&,int);
        void writePop(const std::string&,int);

        std::ostream& _outFile;
        std::string _currentFileName;
    };
}

#endif
