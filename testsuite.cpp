#include "testsuite.h"
#include <iostream>

DebugScanner* DebugScanner::singleton = nullptr;

Lexer TestSuite::lexer = Lexer(DebugScanner::buildScanner(""));
using Data = std::vector<Case>;

DebugScanner* DebugScanner::buildScanner(std::string const& str) {
    if (singleton == nullptr) {
        singleton = new DebugScanner();
    }
    DebugScanner* s = dynamic_cast<DebugScanner*>(singleton);
    s->strs.clear();
    s->strs.insert(s->strs.end(), str.begin(), str.end());
    return s;
}

void TestSuite::integrationTest() {
    identifierTest();
    keywordTest();
    stringTest();
    commentTest();
    singleLineCommentTest();
    directiveTest();
}

void TestSuite::identifierTest() {
    Data data = {
        {"asdfasdf", true},
        {"2asdfads", false},
        {"235423525", false}
    };
    collectionTest<void*>(data, Terminal::ID, [](){
        return lexer.scanIdentifier();
    }, "Identifier");
}

void TestSuite::keywordTest() {
    Data data = {
        {"if", true},
        {"test", false},
        {"ifmain", false},
        {"void", true},
    };
    collectionTest<void*>(data, Terminal::KEYWORD, [](){
        return lexer.scanIdentifier();
    }, "Keyword");
}

void TestSuite::stringTest() {
    Data data = {
        {"\"asdfasdf\"", true},
        {"asdfasdf", false},
        {"\"asdfasdf", false}
    };
    collectionTest<void*>(data, Terminal::STR, []() {
        return lexer.scanString();
    }, "string");
}

void TestSuite::commentTest() {
    Data data = {
        {"/*sadfasdf*/", true},
        {"/***asdfasdf", false},
        {"/*asdf**sdf*/", true}
    };
    collectionTest<void*>(data, Terminal::COMMENT, []() {
        return lexer.scanComment(false);
    }, "comment");
}

void TestSuite::singleLineCommentTest() {
    Data data = {
        {"//liasjioj", true},
        {"/***asdfasdf", false},
        {"/*asdf**sdf*//", false}
    };
    collectionTest<void*>(data, Terminal::COMMENT, []() {
        return lexer.scanSingleLineComment(false);
    }, "singleLineComment");
}

void TestSuite::directiveTest() {
    Data data = {
        {"#include <iostream>", true},
        {"# ifndef", true},
        {"asdfasipsj", false}
    };
    collectionTest<std::string>(data, Terminal::DIRECTIVE, []() {
        return lexer.scanDirective();
    }, "directive");
}
