#include "../headers/code_writer.hpp"

namespace hack {

    CodeWriter::CodeWriter(std::ostream& outFile) : _outFile(outFile)
    {
        // Do nothing
        _outFile << "Test" << std::endl;
    }

    void CodeWriter::setFileName(const std::string& fileName)
    {
        _currentFileName = fileName;
        // TODO: Set symbol name to _currentFileName with extension stripped
    }

    std::string CodeWriter::getFileName() const
    {
        return _currentFileName;
    }

}
