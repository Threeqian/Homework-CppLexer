#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <string>
#include <deque>
#include <vector>
#include "abstractscanner.h"
#include "lexer.h"
#include <iostream>
#include <memory>

class DebugScanner : public AbstractScanner {
    std::deque<char> strs;
    char tmp;
    DebugScanner() = default;
public:
    static std::shared_ptr<DebugScanner> buildScanner(std::string const& str);
    char* peek() override {
        if (strs.empty()) return nullptr;
        tmp = strs.front();
        return &tmp;
    }
    char* take() override {
        if (strs.empty()) return nullptr;
        tmp = strs.front();
        strs.pop_front();
        return &tmp;
    }
    void drop() override {
        if (!strs.empty())
            strs.pop_front();
    }
    bool eof() override {
        return strs.empty();
    }
};

struct Case {
    std::string lexeme;
    bool cond;
};

class TestSuite {
private:
    static Lexer lexer;
    template <typename TokenAttr, typename Lambda>
    static void collectionTest(std::vector<Case> const& collections, Terminal type,
                               Lambda const& f, std::string const& msg) {
        for (auto i : collections) {
            lexer.setScanner(DebugScanner::buildScanner(i.lexeme));
            bool exceptionOccured = false;
            std::string exceptionMsg;
            Token<TokenAttr> result;
            try {
                result = f();
                if (result.terminal != type) throw std::runtime_error("type mismatch");
//            } catch (std::out_of_range const& e) {
//                if (std::string("eof").compare(e.what()) != 0) throw e;
//                /* ignore eof exception */
            } catch (std::exception const& e) {
                exceptionOccured = true;
                exceptionMsg = e.what();
            }
            if (!(exceptionOccured ^ i.cond)) {
                std::cerr << msg << " test failed: \n\t"
                          << i.lexeme << ", " << std::boolalpha
                          << i.cond << "\n" << exceptionMsg << std::endl;
                return;
            }
        }
        std::cerr << msg << " test passed(" << collections.size() << ")." << std::endl;
    }
public:
    static void integrationTest();  // test all of the case below
    static void identifierTest();
    static void keywordTest();
    static void stringTest();
    static void commentTest();
    static void singleLineCommentTest();
    static void directiveTest();
};

#endif // TESTSUITE_H
