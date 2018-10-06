#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include "abstractscanner.h"

class Scanner : public AbstractScanner {
    static Scanner* singleton;
    std::ifstream in;
    std::deque<char> buffer;
    std::string filename;
    char lookAhead = ' ';
    char ret;
    int bufferSize = 0;
    char* dynamicBuf;
    char* scan(bool peek);
    Scanner() = default;
    Scanner(Scanner const& other) = default;
    Scanner& operator=(Scanner const& other) = default;
    void setFilename(std::string const& filename);
public:
    static Scanner* buildScanner(std::string const& filename);
    char* peek() override;
    char* take() override;
    void drop() override;
    bool eof() override { return buffer.empty() && in.eof();}
    int getBufferSize() const {return bufferSize;}
    Scanner& setBufferSize(int size);
    std::string const getFilename() const {return filename;}
};

#endif // SCANNER_H
