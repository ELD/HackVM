#include "headers/code_writer_tests.hpp"
#include "headers/includes.hpp"

void code_writer_init_test_case()
{
    std::stringstream oss;
    hack::CodeWriter writer(oss);

    BOOST_CHECK_MESSAGE(
        typeid(writer).name() == typeid(hack::CodeWriter).name(),
        "Expected type of hack::CodeWriter but didn't get that type"
    );
}

void code_writer_filename_test_case()
{
    std::stringstream oss;
    hack::CodeWriter writer(oss);
    std::string fileName = "test.vm";
    writer.setFileName(fileName);

    BOOST_CHECK_MESSAGE(
        writer.getFileName() == "test.vm",
        "Expected 'test.vm' but received " << writer.getFileName()
    );
}
