#include "../headers/code_writer.hpp"

namespace hack {

    CodeWriter::CodeWriter(std::ostream& outFile) : _outFile(outFile), _eqCounter(0), _ltCounter(0), _gtCounter(0)
    {
        // Do nothing for now
        _outFile << "Test" << std::endl;
    }

    void CodeWriter::setFileName(const std::string& fileName)
    {
        _currentFileName = fileName;
        _eqCounter = 0;
        _ltCounter = 0;
        _gtCounter = 0;
    }

    std::string CodeWriter::getFileName() const
    {
        return _currentFileName;
    }

    std::string CodeWriter::getSymbolName() const
    {
        return _currentFileName.substr(0,_currentFileName.find_first_of('.'));
    }

    void CodeWriter::writeArithmetic(ArithmeticOperations op)
    {
        if (op == ArithmeticOperations::ADD || op == ArithmeticOperations::SUB ||
            op == ArithmeticOperations::AND || op == ArithmeticOperations::OR) {
            writeBinaryArithmetic(op);
        } else if (op == ArithmeticOperations::EQ || op == ArithmeticOperations::GT || op == ArithmeticOperations::LT) {
            writeConditionalArithmetic(op);
        } else {
            writeUnaryArithmetic(op);
        }
    }

    void CodeWriter::writePushPop(CommandType command, const std::string& segment, int index)
    {
        if (command == CommandType::C_PUSH) {
            writePush(segment, index);
        } else if (command == CommandType::C_POP) {
            writePop(segment, index);
        }
    }

    void CodeWriter::writePush(const std::string& command, int index)
    {
        if (command == "local") {
            if (index == 0) {
                _outFile << "@LCL" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@LCL" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "argument") {
            if (index == 0) {
                _outFile << "@ARG" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@ARG" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "this") {
            if (index == 0) {
                _outFile << "@THIS" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@THIS" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "that") {
            if (index == 0) {
                _outFile << "@THAT" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@THAT" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "pointer") {
            if (index == 0) {
                _outFile << "@THIS" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@THAT" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "temp") {
            if (index == 0) {
                _outFile << "@5" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@5" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl;
            }
        } else if (command == "constant") {
            _outFile << "@" << index << std::endl
                << "D=A" << std::endl;
        } else if (command == "static") {
            _outFile << "@" << getFileName() << "." << index << std::endl
                << "D=M" << std::endl;
        }

        _outFile << "@SP" << std::endl
            << "A=M" << std::endl
            << "M=D" << std::endl
            << "@SP" << std::endl
            << "M=M+1" << std::endl;
    }

    void CodeWriter::writePop(const std::string& command, int index)
    {
        // TODO: Finish writing pop assembly code
        if (command == "local") {

        } else if (command == "argument") {

        } else if (command == "this") {

        } else if (command == "that") {

        } else if (command == "pointer") {

        } else if (command == "temp") {

        } else if (command == "constant") {

        } else if (command == "static") {

        }
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
            << "M=M+1" << std::endl;
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
            << "M=M+1" << std::endl;
    }

    void CodeWriter::writeConditionalArithmetic(ArithmeticOperations& op)
    {
        // TODO: Write conditional arithmetic operation assembly
    }

}
