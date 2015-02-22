#include "headers/includes.hpp"

// TODO: Set up test fixture...

bool init_function();
void parser_init_test_case();
void parser_has_more_commands_test_case();

int main(int argc, char* argv[])
{
    return ::boost::unit_test::unit_test_main(&init_function, argc, argv);
}

bool init_function()
{
    auto parser_suite = BOOST_TEST_SUITE("Parser test suite");
    parser_suite->add(BOOST_TEST_CASE(&parser_init_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_has_more_commands_test_case));

    framework::master_test_suite().add(parser_suite);

    return true;
}

void parser_init_test_case()
{
    std::stringstream oss;
    oss << "push constant 7" << std::endl;
    oss << "push constant 15" << std::endl;
    oss << "eq" << std::endl;
    oss << "push constant 17\t// this is a test comment" << std::endl;
    oss << std::endl;

    hack::Parser parser(oss);

    BOOST_CHECK_MESSAGE(
        typeid(parser).name() == typeid(hack::Parser).name(),
        "Expected 'Parser' but received type " << typeid(parser).name()
    );
}

void parser_has_more_commands_test_case()
{
    std::stringstream oss;
    oss << "push constant 7" << std::endl;
    oss << "push constant 15" << std::endl;
    oss << "eq" << std::endl;
    oss << "push constant 17\t// this is a test comment" << std::endl;
    oss << std::endl;

    hack::Parser parser(oss);

    BOOST_CHECK_MESSAGE(
        parser.hasMoreCommands() == true,
        "Expected true but was false"
    );

    parser.advance();

    BOOST_CHECK_MESSAGE(
        parser.getCurrentCommand() == "push constant 7",
        "Expected 'push constant 7' but received " << parser.getCurrentCommand()
    );

    parser.advance();
    parser.advance();
    parser.advance();

    BOOST_CHECK_MESSAGE(
        parser.getCurrentCommand() == "push constant 17",
        "Expected command without comments but they weren't stripped correctly."
        << "Received: " << parser.getCurrentCommand()
    );
}
