#include "../headers/code_writer.hpp"

namespace hack {

    CodeWriter::CodeWriter(std::ostream& outFile) : _outFile(outFile) , _currentFileName("") , _funcName("") ,
    _eqCounter(0) , _ltCounter(0) , _gtCounter(0), _retCounter(0)
    {
        // Do nothing for now
    }

    void CodeWriter::setFileName(const std::string& fileName)
    {
        _currentFileName = fileName;
    }

    std::string CodeWriter::getFileName() const
    {
        return _currentFileName;
    }

    std::string CodeWriter::getSymbolName() const
    {
        return _currentFileName.substr(0,_currentFileName.find_first_of('.'));
    }

    void CodeWriter::writeInit()
    {
        _outFile << "// Write init code" << std::endl;

        // Set SP=256
        _outFile << "@256" << std::endl
            << "D=A" << std::endl
            << "@SP" << std::endl
            << "M=D" << std::endl
            << std::endl;

        _outFile << "// Push everything onto stack" << std::endl;

        // Push return address onto stack
        _outFile << "@Return" << _retCounter << std::endl
            << "D=A" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        // Push LCL, ARG, THIS, THAT
        _outFile << "@LCL" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@ARG" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@THIS" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@THAT" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        // ARG=SP-5
        _outFile << "@SP" << std::endl
            << "D=M" << std::endl
            << "@5" << std::endl
            << "D=D-A" << std::endl
            << "@ARG" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // LCL=SP
        _outFile << "@SP" << std::endl
            << "D=M" << std::endl
            << "@LCL" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // goto function

        _outFile << "// Call Sys.init" << std::endl;

        _outFile << "@Sys.init" << std::endl
            << "0;JMP" << std::endl
            << std::endl;

        // (ReturnLabel)
        _outFile << "(Return" << _retCounter << ")" << std::endl;
        ++_retCounter;
    }

    void CodeWriter::writeArithmetic(ArithmeticOperations op)
    {
        _outFile << "// Write arithmetic operation" << std::endl;
        if (op == ArithmeticOperations::ADD || op == ArithmeticOperations::SUB ||
            op == ArithmeticOperations::AND || op == ArithmeticOperations::OR) {
            writeBinaryArithmetic(op);
        } else if (op == ArithmeticOperations::EQ || op == ArithmeticOperations::GT || op == ArithmeticOperations::LT) {
            writeConditionalArithmetic(op);
        } else {
            writeUnaryArithmetic(op);
        }
    }

    void CodeWriter::writePushPop(CommandType command, const std::string& segment, const int& index)
    {
        std::string pushOrPop;
        if (command == CommandType::C_PUSH) {
            pushOrPop = "push";
        } else {
            pushOrPop = "pop";
        }

        _outFile << "// " << pushOrPop << " " << segment << " " << index << std::endl;

        if (command == CommandType::C_PUSH) {
            writePush(segment, index);
        } else if (command == CommandType::C_POP) {
            writePop(segment, index);
        }
    }

    void CodeWriter::writeLabel(const std::string& label)
    {
        _outFile << "(" << _funcName << "$" << label << ")" << std::endl;
    }

    void CodeWriter::writeGoto(const std::string& label)
    {
        _outFile << "// Write goto" << std::endl;
        _outFile << "@" << _funcName << "$" << label << std::endl
            << "0;JMP" << std::endl
            << std::endl;
    }

    void CodeWriter::writeIf(const std::string& label)
    {
        _outFile << "// Write if" << std::endl;
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M" << std::endl
            << "@" << _funcName << "$" << label << std::endl
            << "D;JNE" << std::endl
            << std::endl;
    }

    void CodeWriter::writeFunction(const std::string& functionName, const int& numLocals)
    {
        _outFile << "// Function " << functionName << std::endl;
        _funcName = functionName;
        _outFile << "(" << _funcName << ")" << std::endl;

        for (int i = 0; i < numLocals; i++) {
            writePushPop(CommandType::C_PUSH, "constant", 0);
        }
    }

    void CodeWriter::writeCall(const std::string& functionName, const int& numLocals)
    {
        _outFile << "// Calling function " << functionName << std::endl;
        _outFile << "@Return" << _retCounter << std::endl
            << "D=A" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        // Push LCL, ARG, THIS, THAT
        _outFile << "@LCL" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@ARG" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@THIS" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        _outFile << "@THAT" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;

        // ARG=SP-(numLocals + 5)
        _outFile << "@SP" << std::endl
            << "D=M" << std::endl
            << "@" << numLocals + 5 << std::endl
            << "D=D-A" << std::endl
            << "@ARG" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // LCL=SP
        _outFile << "@SP" << std::endl
            << "D=M" << std::endl
            << "@LCL" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // goto function
        _outFile << "@" << functionName << std::endl
            << "0;JMP" << std::endl
            << std::endl;

        // (ReturnLabel)
        _outFile << "(Return" << _retCounter << ")" << std::endl
            << std::endl;

        ++_retCounter;
    }

    void CodeWriter::writeReturn()
    {
        _outFile << "// Writing return" << std::endl;
        // Set FRAME to R13
        _outFile << "@LCL" << std::endl
            << "D=M" << std::endl
            << "@R13" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set Ret to *(FRAME-5)
        pushFrameOffsetToD(5);
        _outFile << "@R14" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set *ARG to the top stack value
        popToD();
        _outFile << "@ARG" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set SP to ARG+1
        _outFile << "@ARG" << std::endl
            << "D=M+1" << std::endl
            << "@SP" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set THAT to *(FRAME-1)
        pushFrameOffsetToD(1);
        _outFile << "@THAT" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set THIS to *(FRAME-2)
        pushFrameOffsetToD(2);
        _outFile << "@THIS" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set ARG to *(FRAME-3)
        pushFrameOffsetToD(3);
        _outFile << "@ARG" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // Set LCL to *(FRAME-4)
        pushFrameOffsetToD(4);
        _outFile << "@LCL" << std::endl
            << "M=D" << std::endl
            << std::endl;

        // goto RET
        _outFile << "@R14" << std::endl
            << "A=M" << std::endl
            << "0;JMP" << std::endl
            << std::endl;
    }

    void CodeWriter::writePush(const std::string& command, const int& index)
    {
        pushToD(command, index);
        pushDToStack();

        _outFile << std::endl;
    }

    void CodeWriter::writePop(const std::string& command, const int& index)
    {
        popToMemory(command, index);
        _outFile << std::endl;
    }

    void CodeWriter::popToD()
    {
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M" << std::endl;
    }

    void CodeWriter::popToMemory(const std::string& command, const int& index)
    {
        if (command == "this" || command == "that" || command == "local" || command == "argument") {
            if (index > 0) {
                _outFile << commandTypeLabel(command) << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                popToD();
                _outFile << commandTypeLabel(command) << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "pointer" || command == "temp") {
            if (index > 0) {
                _outFile << commandTypeLabel(command) << std::endl
                    << "D=A" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                popToD();
                _outFile << commandTypeLabel(command) << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "static") {
            popToD();
            _outFile << "@" << getFileName() << "." << index << std::endl
                << "M=D" << std::endl;
        }
    }

    void CodeWriter::pushToD(const std::string& command, const int& index)
    {
        if (command == "this" || command == "that" || command == "local" || command == "argument") {
            _outFile << commandTypeLabel(command) << std::endl;

            if (index > 0) {
                _outFile << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "A=M" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "pointer" || command == "temp") {
            _outFile << commandTypeLabel(command) << std::endl;

            if (index > 0) {
                _outFile << "D=A" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "D=M" << std::endl;
            }
        } else if (command == "static") {
            _outFile << "@" << _currentFileName << "." << index << std::endl
                << "D=M" << std::endl;
        } else {
            _outFile << "@" << index << std::endl
                << "D=A" << std::endl;
        }
    }

    void CodeWriter::pushDToStack()
    {
        _outFile << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl;
    }

    void CodeWriter::pushFrameOffsetToD(const int& offset)
    {
        _outFile << "@R13" << std::endl
            << "D=M" << std::endl
            << "@" << offset << std::endl
            << "A=D-A" << std::endl
            << "D=M" << std::endl;
    }

    void CodeWriter::writeBinaryArithmetic(ArithmeticOperations& op)
    {
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "AM=M-1" << std::endl;
        if (op == ArithmeticOperations::ADD) {
            _outFile << "M=M+D" << std::endl;
        } else if (op == ArithmeticOperations::SUB) {
            _outFile << "M=M-D" << std::endl;
        } else if (op == ArithmeticOperations::AND) {
            _outFile << "M=M&D" << std::endl;
        } else if (op == ArithmeticOperations::OR) {
            _outFile << "M=M|D" << std::endl;
        }

        _outFile << "@SP" << std::endl
            << "M=M+1" << std::endl << std::endl;
    }

    void CodeWriter::writeUnaryArithmetic(ArithmeticOperations& op)
    {
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl;

        if (op == ArithmeticOperations::NOT) {
            _outFile << "M=!M" << std::endl;
        } else if (op == ArithmeticOperations::NEG) {
            _outFile << "M=-M" << std::endl;
        }

        _outFile << "@SP" << std::endl
            << "M=M+1" << std::endl << std::endl;
    }

    void CodeWriter::writeConditionalArithmetic(ArithmeticOperations& op)
    {
        std::stringstream labelStream;
        std::string label;
        std::string conditionalString;
        if (op == ArithmeticOperations::EQ) {
            labelStream << "EQ." << _eqCounter;
            label = labelStream.str();
            ++_eqCounter;
            conditionalString = "D;JEQ";
        } else if (op == ArithmeticOperations::LT) {
            labelStream << "LT." << _ltCounter;
            label = labelStream.str();
            ++_ltCounter;
            conditionalString = "D;JLT";
        } else if (op == ArithmeticOperations::GT) {
            labelStream << "GT." << _gtCounter;
            label = labelStream.str();
            ++_gtCounter;
            conditionalString = "D;JGT";
        }
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M" << std::endl
            << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M-D" << std::endl
            << "@" << label << ".TRUE" << std::endl
            << conditionalString << std::endl
            << "@" << label <<  ".FALSE" << std::endl
            << "0;JMP" << std::endl
            << "(" << label << ".TRUE)" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=-1" << std::endl
            << "@" << label << ".END" << std::endl
            << "0;JMP" << std::endl
            << "("  << label << ".FALSE)" << std::endl
            << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=0" << std::endl
            << "@" << label << ".END" << std::endl
            << "0;JMP" << std::endl
            << "(" << label << ".END)" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl
            << std::endl;
    }

    std::string CodeWriter::commandTypeLabel(const std::string& label)
    {
        std::string returnLabel;
        if (label == "this") {
            returnLabel = "@THIS";
        } else if (label == "that") {
            returnLabel = "@THAT";
        } else if (label == "local") {
            returnLabel = "@LCL";
        } else if (label == "argument") {
            returnLabel = "@ARG";
        } else if (label == "pointer") {
            returnLabel = "@THIS";
        } else {
            returnLabel = "@5";
        }

        return returnLabel;
    }

}
