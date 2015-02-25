#include "../headers/includes.hpp"
#include "../headers/utilities.hpp"
#include "../headers/parser.hpp"
#include "../headers/code_writer.hpp"

int main(int argc, char* argv[])
{
    // TODO: Directory handling, multiple files, full application
    // TODO: Fix issue with CodeWriter handling pop commands
    if (argc < 2) {
        std::cout << "No argument sent in." << std::endl << "Example usage: ./hackvm [file|directory]" << std::endl;
        return -1;
    }

    if (std::string(argv[1]).find("--help") != std::string::npos ||
        std::string(argv[1]).find("-h") != std::string::npos) {
        std::cout << "Example usage: ./hackvm [file|directory]" << std::endl;
        return 0;
    }

    std::string inFileName{argv[1]};
    std::string outFileName{inFileName.substr(0,inFileName.find_last_of('.')) + ".asm"};
    std::string shortFileName{hack::utilities::getShortFileName(inFileName)};
    std::cout << shortFileName << std::endl;

    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);

    hack::Parser parser(inFile);
    hack::CodeWriter writer(outFile);

    writer.setFileName(shortFileName);

    while(parser.hasMoreCommands()) {
        parser.advance();
        // std::cout << "Command: " << parser.getCurrentCommand() << std::endl;
        // std::cout << "Command type: " << hack::utilities::commandTypeAsString(parser.commandType()) << std::endl;
        if (parser.commandType() == hack::CommandType::C_PUSH || parser.commandType() == hack::CommandType::C_POP) {
            writer.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());
        } else {
            writer.writeArithmetic(hack::utilities::arithmeticCommandToOperation(parser.getCurrentCommand()));
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}
