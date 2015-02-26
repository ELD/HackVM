#include "headers/parser_tests.hpp"
#include "headers/includes.hpp"

void parser_init_test_case()
{
    std::stringstream oss;
    mockInputStream(oss);

    hack::Parser parser(oss);

    BOOST_CHECK_MESSAGE(
        typeid(parser).name() == typeid(hack::Parser).name(),
        "Expected 'Parser' but received type " << typeid(parser).name()
    );
}

void parser_has_more_commands_test_case()
{
    std::stringstream oss;
    mockInputStream(oss);

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

void parser_command_type_test_case()
{
    std::stringstream oss;
    mockInputStream(oss);

    hack::Parser parser(oss);

    parser.advance();
    BOOST_CHECK_MESSAGE(
        parser.commandType() == hack::CommandType::C_PUSH,
        "Expected command C_PUSH but received " << hack::utilities::commandTypeAsString(parser.commandType())
    );

    parser.advance();
    BOOST_CHECK_MESSAGE(
        parser.commandType() == hack::CommandType::C_PUSH,
        "Expected command C_PUSH but received " << hack::utilities::commandTypeAsString(parser.commandType())
    );

    parser.advance();
    BOOST_CHECK_MESSAGE(
        parser.commandType() == hack::CommandType::C_ARITHMETIC,
        "Expected command C_ARITHMETIC but received " << hack::utilities::commandTypeAsString(parser.commandType())
    );
}

void parser_get_args_test_case()
{
    std::stringstream oss;
    mockInputStream(oss);

    hack::Parser parser(oss);

    parser.advance();
    BOOST_CHECK_MESSAGE(
        parser.arg1() == "constant",
        "Expected 'constant' but received " << parser.arg1()
    );

    BOOST_CHECK_MESSAGE(
        parser.arg2() == "7",
        "Expected '7' but received " << parser.arg2()
    );
}
