#ifndef _CODE_WRITER_H_
#define _CODE_WRITER_H_

#include "includes.hpp"

namespace hack {

    class CodeWriter {
    public:
        CodeWriter() = default;
        CodeWriter(std::ostream&);
        ~CodeWriter() = default;
        CodeWriter(const CodeWriter&) = delete;
        CodeWriter(CodeWriter&&) = delete;
        void setFileName(const std::string&);

        std::string getFileName() const;
        std::string getSymbolName() const;
    private:
        std::ostream& _outFile;
        std::string _currentFileName;
    };
}

#endif
