#ifndef _CODE_WRITER_H_
#define _CODE_WRITER_H_

#include "includes.hpp"
#include "../headers/arithmetic_operations.hpp"
#include "../headers/command_type.hpp"
#include "utilities.hpp"

namespace hack {

    class CodeWriter {
    public:
        CodeWriter() = default;
        CodeWriter(std::ostream&);
        ~CodeWriter() = default;
        CodeWriter(const CodeWriter&) = delete;
        CodeWriter(CodeWriter&&) = delete;
        void setFileName(const std::string&);
        void writeInit();
        void writeArithmetic(ArithmeticOperations);
        void writePushPop(CommandType, const std::string&, const int&);
        void writeLabel(const std::string&);
        void writeGoto(const std::string&);
        void writeIf(const std::string&);
        void writeFunction(const std::string&, const int&);
        void writeCall(const std::string&, const int&);
        void writeReturn();

        std::string getFileName() const;
        std::string getSymbolName() const;
    private:
        void writePush(const std::string&,const int&);
        void writePop(const std::string&,const int&);
        void popToD();
        void popToMemory(const std::string&, const int&);
        void pushToD(const std::string&, const int&);
        void pushDToStack();
        void pushFrameOffsetToD(const int&);
        void writeBinaryArithmetic(ArithmeticOperations&);
        void writeUnaryArithmetic(ArithmeticOperations&);
        void writeConditionalArithmetic(ArithmeticOperations&);
        std::string commandTypeLabel(const std::string&);

        std::ostream& _outFile;
        std::string _currentFileName;
        std::string _funcName;

        int _eqCounter;
        int _ltCounter;
        int _gtCounter;
        int _retCounter;
    };
}

#endif
