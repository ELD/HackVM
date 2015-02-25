#include "../headers/code_writer.hpp"

namespace hack {

    CodeWriter::CodeWriter(std::ostream& outFile) : _outFile(outFile)
    {
        // Do nothing
        _outFile << "Test" << std::endl;
    }

    void CodeWriter::setFileName(const std::string& fileName)
    {
        _currentFileName = fileName;
        // TODO: Set symbol name to _currentFileName with extension stripped
    }

    std::string CodeWriter::getFileName() const
    {
        return _currentFileName;
    }

    std::string CodeWriter::getSymbolName() const
    {
        return _currentFileName.substr(0,_currentFileName.find_first_of('.'));
    }

    void CodeWriter::writeArithmetic(ArithmeticOperations& op)
    {
        switch (op) {
            case ArithmeticOperations::ADD:
                _outFile << "ADD" << std::endl;
                break;
            case ArithmeticOperations::SUB:
                _outFile << "SUB" << std::endl;
                break;
            case ArithmeticOperations::NEG:
                _outFile << "NEG" << std::endl;
                break;
            case ArithmeticOperations::EQ:
                _outFile << "EQ" << std::endl;
                break;
            case ArithmeticOperations::GT:
                _outFile << "GT" << std::endl;
                break;
            case ArithmeticOperations::LT:
                _outFile << "LT" << std::endl;
                break;
            case ArithmeticOperations::AND:
                _outFile << "AND" << std::endl;
                break;
            case ArithmeticOperations::OR:
                _outFile << "OR" << std::endl;
                break;
            case ArithmeticOperations::NOT:
                _outFile << "NOT" << std::endl;
                break;
            default:
                break;
        }
    }

    void CodeWriter::writePushPop(CommandType& command, const std::string& segment, int index)
    {
        if (command == CommandType::C_PUSH) {
            writePush(segment, index);
        } else if (command == CommandType::C_POP) {
            writePop(segment, index);
        }
    }

    void CodeWriter::writePush(const std::string& command, int index)
    {
        if (command == "local") {a
            if (index == 0) {
                _outFile << "@LCL" << std::endl
                    << "A=M" << std::endl
                    << "D=M" << std::endl;
            } else {
                _outFile << "@LCL" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "A=D+A" << std::endl
                    << "D=M" << std::endl
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
                    << "D=M" << std::endl
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

    }

}
