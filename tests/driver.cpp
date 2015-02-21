#include "headers/includes.hpp"

bool init_function();
void parser_init_test_case();

int main(int argc, char* argv[])
{
    return ::boost::unit_test::unit_test_main(&init_function, argc, argv);
}

bool init_function()
{
    auto parser_suite = BOOST_TEST_SUITE("Parser test suite");
    parser_suite->add(BOOST_TEST_CASE(&parser_init_test_case));

    framework::master_test_suite().add(parser_suite);

    return true;
}

void parser_init_test_case()
{
    hack::Parser parser;

    BOOST_CHECK_MESSAGE(
        typeid(parser).name() == typeid(hack::Parser).name(),
        "Expected 'Parser' but received type " << typeid(parser).name()
    );
}
