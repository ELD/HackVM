#include "../headers/includes.hpp"
#include "../headers/utilities.hpp"
#include "../headers/parser.hpp"

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

    std::fstream inFile(argv[1]);

    hack::Parser parser(inFile);

    while(parser.hasMoreCommands()) {
        parser.advance();
        std::cout << "Command: " << parser.getCurrentCommand() << std::endl;
        std::cout << "Command type: " << hack::utilities::commandTypeAsString(parser.commandType()) << std::endl;
    }

    return 0;
}
