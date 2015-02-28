#include "../headers/includes.hpp"
#include "../headers/utilities.hpp"
#include "../headers/parser.hpp"
#include "../headers/code_writer.hpp"

/**
 * TODO: Extensive refactoring in CodeWriter module, especially
 * TODO: Write more extensive and well-structure unit tests
 * TODO: Fix BasicTest output issue
 * TODO: Directory handling, multiple files, full application
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

    if (boost::filesystem::is_regular_file(fileOrDirectory)) {
        std::cout << "Is only a single file." << std::endl;
    } else {
        std::cout << "Is a directory." << std::endl;
        auto files = hack::utilities::getVmFiles(fileOrDirectory);
        std::cout << "Size of directory: " << files.size() << std::endl;
        for (const auto& file : files) {
            std::cout << "File name: " << file << std::endl;
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

    while(parser.hasMoreCommands()) {
        parser.advance();
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
