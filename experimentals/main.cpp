#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string input = "+12 -12 -13 90 qwerty";
    std::regex pattern("([+-]?[[:digit:]]+)|([[:alpha:]]+)");

    auto iter_begin = std::sregex_token_iterator(input.begin(), input.end(), pattern, 1);
    auto iter_end = std::sregex_token_iterator();

    for (auto it = iter_begin; it != iter_end; ++it)
    {
        std::ssub_match match = *it;
        std::cout << "Match: " << match.str() << " [" << match.length() << "]" << std::endl;
    }

    std::cout << std::endl << "Done matching..." << std::endl;

    return 0;
}
