#include "headers/includes.hpp"
#include "headers/parser_tests.hpp"
#include "headers/code_writer_tests.hpp"

// TODO: Set up test fixture...

bool init_function();

int main(int argc, char* argv[])
{
    return ::boost::unit_test::unit_test_main(&init_function, argc, argv);
}

bool init_function()
{
    auto parser_suite = BOOST_TEST_SUITE("Parser test suite");
    parser_suite->add(BOOST_TEST_CASE(&parser_init_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_has_more_commands_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_command_type_test_case));
    parser_suite->add(BOOST_TEST_CASE(&parser_get_args_test_case));

    auto code_writer_suite = BOOST_TEST_SUITE("Code Writer Test Suite");
    code_writer_suite->add(BOOST_TEST_CASE(&code_writer_init_test_case));
    code_writer_suite->add(BOOST_TEST_CASE(&code_writer_filename_test_case));

    framework::master_test_suite().add(parser_suite);
    framework::master_test_suite().add(code_writer_suite);

    return true;
}
