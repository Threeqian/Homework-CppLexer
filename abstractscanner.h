#ifndef ABSTRACTSCANNER_H
#define ABSTRACTSCANNER_H

#include <string>
class AbstractScanner {
public:
    virtual char* peek() = 0;
    virtual char* take() = 0;
    virtual void drop() = 0;
    virtual bool eof() = 0;
    virtual ~AbstractScanner();
};

#endif // ABSTRACTSCANNER_H
