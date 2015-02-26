#include "utilities.hpp"

void mockInputStream(std::stringstream& oss)
{
    oss << "push constant 7" << std::endl;
    oss << "push constant 15" << std::endl;
    oss << "eq" << std::endl;
    oss << "push constant 17\t// this is a test comment" << std::endl;
    oss << std::endl;
}
