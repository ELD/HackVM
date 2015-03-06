#include "../headers/includes.hpp"
#include "../headers/utilities.hpp"
#include "../headers/parser.hpp"
#include "../headers/code_writer.hpp"

/**
 * TODO: Write more extensive and well-structure unit tests
 * TODO: Fix BasicTest output issue
 * TODO: Directory handling, multiple files, full application
 * TODO: Use std::async to compile multiple vm files
 */

int main(int argc, char* argv[])
{
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

    // Check if the file name supplied is a directory
    boost::filesystem::path fileOrDirectory{inFileName};
    std::vector<std::string> files;

    if (boost::filesystem::is_regular_file(fileOrDirectory)) {
        std::cout << "Is only a single file." << std::endl;
    } else {
        files = hack::utilities::getVmFiles(fileOrDirectory);
        for (auto& file : files) {
            std::cout << file << std::endl;
        }

        return 0;
    }

    std::string outFileName{inFileName.substr(0,inFileName.find_last_of('.')) + ".asm"};
    std::string shortFileName{hack::utilities::getShortFileName(inFileName)};

    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);

    hack::Parser parser(inFile);
    hack::CodeWriter writer(outFile);

    writer.setFileName(shortFileName);
    writer.writeInit();

    while(parser.hasMoreCommands()) {
        parser.advance();
        std::cout << "Current command: " << parser.getCurrentCommand() << std::endl;
        std::cout << "Command type: " << hack::utilities::commandTypeAsString(parser.commandType()) << std::endl;
        if (parser.commandType() == hack::CommandType::C_PUSH || parser.commandType() == hack::CommandType::C_POP) {
            writer.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());
        } else if (parser.commandType() == hack::CommandType::C_GOTO) {
            writer.writeGoto(parser.arg1());
        } else if (parser.commandType() == hack::CommandType::C_IF) {
            writer.writeIf(parser.arg1());
        } else if (parser.commandType() == hack::CommandType::C_LABEL) {
            writer.writeLabel(parser.arg1());
        } else if (parser.commandType() == hack::CommandType::C_FUNCTION) {
            writer.writeFunction(parser.arg1(), parser.arg2());
        } else if (parser.commandType() == hack::CommandType::C_RETURN) {
            writer.writeReturn();
        } else if (parser.commandType() == hack::CommandType::C_CALL) {
            writer.writeCall(parser.arg1(), parser.arg2());
        } else {
            writer.writeArithmetic(hack::utilities::arithmeticCommandToOperation(parser.getCurrentCommand()));
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}
