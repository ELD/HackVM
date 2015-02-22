#include "../headers/includes.hpp"
#include "../headers/utilities.hpp"

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

    std::cout << "Directory name: " << argv[1] << std::endl;

    std::cout << "Enum: " << hack::utilities::commandTypeAsString(hack::CommandType::C_PUSH) << std::endl;

    return 0;
}
