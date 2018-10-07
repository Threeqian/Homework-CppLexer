#include "scanner.h"
#include <stdexcept>
#include <QDir>
#include <iterator>

void Scanner::setBufferSize(int size) {
    if (size > 0) {
        if (!dynamicBuf) delete dynamicBuf;
        dynamicBuf = new char[size];
        bufferSize = size;
    }
    else throw std::runtime_error("bufferSize < 0");
}

void Scanner::setFilename(std::string const& filename) {
    QDir directory;
    if (!directory.exists(QString(filename.c_str()))) {
        throw std::runtime_error("file not exists");
    }
    in.clear();
    in.open(filename, std::ios_base::in);
    if (!in.is_open()) {
        throw std::runtime_error("opening file error");
    }
    this->filename = filename;
}


char* Scanner::scan(bool peek) {
    if (bufferSize == 0) return nullptr;
    if (buffer.empty()) {
        if (in.eof()) return nullptr;
        // read *bufferSize* characters into buffer
        in.read(dynamicBuf, bufferSize);
        long readSize = in.gcount();
        if (readSize == 0) return nullptr;
        buffer.insert(buffer.end(), &dynamicBuf[0], &dynamicBuf[readSize]);
    }
    lookAhead = buffer.front();
    if (!peek) buffer.pop_front();
    return &lookAhead;
}

std::shared_ptr<Scanner> Scanner::buildScanner(std::string const& filename) {
    std::shared_ptr<Scanner> s(new Scanner);
    s->setBufferSize(64);
    s->setFilename(filename);
    s->lookAhead = ' ';
    return s;
}

Scanner::~Scanner() {
    if (!dynamicBuf) delete dynamicBuf;
}

char* Scanner::peek() {
    return scan(true);
}

void Scanner::drop() {
    scan(false);
}

char* Scanner::take() {
    return scan(false);
}
