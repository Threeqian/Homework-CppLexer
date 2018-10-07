#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include "abstractscanner.h"
#include <memory>

class Scanner : public AbstractScanner {
    std::ifstream in;
    std::deque<char> buffer;
    std::string filename;
    char lookAhead = ' ';
    int bufferSize = 0;
    char* dynamicBuf = nullptr;
    char* scan(bool peek);
    Scanner() = default;
    Scanner(Scanner const& other) = delete;
    Scanner& operator=(Scanner const& other) = delete;
    void setFilename(std::string const& filename);
public:
    static std::shared_ptr<Scanner> buildScanner(std::string const& filename);
    ~Scanner() override;
    char* peek() override;
    char* take() override;
    void drop() override;
    bool eof() override { return buffer.empty() && in.eof();}
    int getBufferSize() const {return bufferSize;}
    void setBufferSize(int size);
    std::string const getFilename() const {return filename;}
};

#endif // SCANNER_H
