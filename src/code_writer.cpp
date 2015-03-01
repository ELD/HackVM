#include "../headers/code_writer.hpp"

namespace hack {

    CodeWriter::CodeWriter(std::ostream& outFile) : _outFile(outFile), _eqCounter(0), _ltCounter(0), _gtCounter(0)
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
        pushToD(command, index);
        pushDToStack();

        _outFile << std::endl;
    }

    void CodeWriter::writePop(const std::string& command, int index)
    {
        if (command == "local") {
            if (index == 0) {
                popToD();
                _outFile << "@LCL" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                _outFile << "@LCL" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "argument") {
            if (index == 0) {
                popToD();
                _outFile << "@ARG" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                _outFile << "@ARG" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "this") {
            if (index == 0) {
                popToD();
                _outFile << "@THIS" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                _outFile << "@THIS" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "that") {
            if (index == 0) {
                popToD();
                _outFile << "@THAT" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            } else {
                _outFile << "@THAT" << std::endl
                    << "D=M" << std::endl
                    << "@" << index << std::endl
                    << "D=D+A" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "pointer") {
            if (index == 0) {
                popToD();
                _outFile << "@THIS" << std::endl
                    << "M=D" << std::endl;
            } else {
                popToD();
                _outFile << "@THAT" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "temp") {
            if (index == 0) {
                popToD();
                _outFile << "@5" << std::endl
                    << "M=D" << std::endl;
            } else {
                _outFile << "@5" << std::endl
                    << "D=A" << std::endl
                    << "@" << index << std::endl
                    << "D=A+D" << std::endl
                    << "@R13" << std::endl
                    << "M=D" << std::endl;
                popToD();
                _outFile << "@R13" << std::endl
                    << "A=M" << std::endl
                    << "M=D" << std::endl;
            }
        } else if (command == "static") {
            popToD();
            _outFile << "@" << getFileName() << "." << index << std::endl
                << "M=D" << std::endl;
        }

        _outFile << std::endl;
    }

    void CodeWriter::popToD()
    {
        _outFile << "@SP" << std::endl
            << "AM=M-1" << std::endl
            << "D=M" << std::endl;
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
                _outFile << "A=M " << std::endl
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
        } else{
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
