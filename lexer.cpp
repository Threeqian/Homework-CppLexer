#include "lexer.h"
#include <cctype>
#include "keywords.cpp"
#include "abstractscanner.h"
#include "tokenhandler.h"

static const char blank = ' ';

Lexer::Lexer(AbstractScanner* scanner) {
    if (!scanner) throw std::runtime_error("scanner unavailable");
    this->scanner = scanner;
}

void Lexer::setScanner(AbstractScanner* scanner) {
    if (!scanner) throw std::runtime_error("scanner unavailable");
    this->scanner = scanner;
}

//// warning: never use take_s or peek_s to skip blank
char Lexer::take_s() {     // safe scaning
    if (eof()) throw std::out_of_range("eof");
    char* pch = scanner->take();
    if (pch == nullptr) {
        if (eof()) return blank;
        throw std::runtime_error("take_s");
    }
    return *pch;
}

char Lexer::peek_s() {     // safe peeking
    //if (eof()) throw std::out_of_range("eof");
    char* pch = scanner->peek();
    if (pch == nullptr) {
        if (eof()) return blank;
        throw std::runtime_error("take_s");
    }
    return *pch;
}

inline bool Lexer::eof() {return scanner->eof();}

// alpha [digit | alpha]*
Token<void*> Lexer::scanIdentifier() {
    std::string result;
    makeSure(std::isalpha(peek_s()) || peek_s() == '_', "scanId::isalpha");
    result.push_back(take_s());
    while (std::isdigit(peek_s()) || std::isalpha(peek_s()) || peek_s() == '_') {
        result.push_back(take_s());
    }

    // keyword or identifier
    if (Perfect_Hash::in_word_set(result.c_str(), static_cast<unsigned int>(result.size()))) {
        return Token<void*>{result, Terminal::KEYWORD, nullptr,  "keyword"};
    }
    return Token<void*>{result, Terminal::ID, nullptr,  "identifier"};
}

// digits = digit | digit digit*
// digits (.digits)? (E digits)?
Token<NumType> Lexer::scanNumber() {
    std::string result;
    auto handleDigits = [&](){
        makeSure(std::isdigit(peek_s()), "handleDigits::isdigit");
        result.push_back(take_s());
        while (std::isdigit(peek_s())) {
            result.push_back(take_s());
        }
    };
    auto handleE = [&]() -> bool {
        if (peek_s() != 'E' && peek_s() != 'e') return false;
        result.push_back(take_s());
        if (peek_s() == '+' || peek_s() == '-') result.push_back(take_s());
        handleDigits();
        return true;
    };
    auto handlePoint = [&]() -> bool {
        if (peek_s() != '.') return false;
        result.push_back(take_s());
        handleDigits();
        return true;
    };
    handleDigits();
    if ((handlePoint() | handleE()) != 0) {  // is floating
        return Token<NumType>{result, Terminal::NUM, NumType::Floating,  "floating"};
    }
    return Token<NumType>{result, Terminal::NUM, NumType::Integer, "integer"};
}

// quoted with ""
Token<void*> Lexer::scanString() {
    std::string result;
    makeSure(peek_s() == '\"', "scanString::isquote");
    result.push_back(take_s());
    while (peek_s() != '\"') result.push_back(take_s());
    result.push_back(take_s());
    return Token<void*>{result, Terminal::STR, nullptr, "literal string"};
}

Token<void*> Lexer::scanChar() {
    std::string result;
    makeSure(peek_s() == '\'', "scanChar::isquote");
    result.push_back(take_s());
    while (peek_s() != '\'') result.push_back(take_s());
    result.push_back(take_s());
    return Token<void*>{result, Terminal::STR, nullptr, "char"};
}

// quoted with /**/
Token<void*> Lexer::scanComment(bool alreadyReadFront) {
    std::string result = "/*";
    if (!alreadyReadFront) {
        makeSure(take_s() == '/', "scanComment");
    }
    makeSure(take_s() == '*', "scanComment::isbegin");
    int state = 0;
    while (1) {
        switch (state) {
        case 0: {   // continue reading comments
            while (peek_s() != '*') result.push_back(take_s());
            result.push_back('*');
            state = 1;
            break;
        }
        case 1: {   // an asterisk occurred
            while (peek_s() == '*') result.push_back(take_s());
            if (peek_s() != '/') {
                result.push_back(take_s());
                state = 0;
                break;
            } else {
                result.push_back('/');
                return Token<void*>(result, Terminal::COMMENT, nullptr, "comment");
            }
        }
        }
    }
}

// begin with //
Token<void*> Lexer::scanSingleLineComment(bool alreadyReadFront) {
    std::string result("/");
    if (!alreadyReadFront) {
        makeSure(take_s() == '/', "scanSingleLineComment::isbegin");
        result.push_back('/');
    }
    makeSure(take_s() == '/', "scanSingleLineComment::isbegin");
    result.push_back('/');
    while (peek_s() != '\n' && !eof()) result.push_back(take_s());
    return Token<void*>{result, Terminal::COMMENT, nullptr, "comment"};
}

// splitter: (){}[];:?
Token<void*> Lexer::scanSplitter() {
    char ch = take_s();
    std::string result;
    result.push_back(ch);
    std::string value;
    switch (ch) {
    case '(' : value = "left parenthesis"; break;
    case ')' : value = "right parenthesis"; break;
    case '{' : value = "left brace"; break;
    case '}' : value = "right brace"; break;
    case '[' : value = "left bracket"; break;
    case ']' : value = "right bracket"; break;
    case ';' : value = "semicolon"; break;
    case ':' : value = "colon"; break;
    case '?' : value = "questionMark"; break;
    }
    return Token<void*>{result, Terminal::SPLITTER, nullptr, value};
}

// begin with #
Token<std::string> Lexer::scanDirective() {
    std::string result;
    std::string value;
    makeSure(peek_s() == '#', "scanDirective::is#");
    bool flag = false;
    while (peek_s() != '\n' && !eof()) {
        if (peek_s() == '<') flag = true;
        if (peek_s() == '>') flag = false;
        if (flag) value.push_back(peek_s());
        result.push_back(take_s());
    }
    return Token<std::string>{result, Terminal::DIRECTIVE, value, "directive"};
}

Token<void*> Lexer::scanOperator() {
    static const std::string sOper = ".~^,";
    char ch = peek_s();
    switch (ch) {
    case '+': return plus();
    case '-': return minus();
    case '*': return multiple();
    case '%': return mod();
    case '&': return ref();
    case '|': return bitwiseOr();
    case '!': return exclam();
    case '<': return lessThan();
    case '>': return greaterThan();
    case '=': return equal();
    default: {
        if (sOper.find(ch) != sOper.npos) return singleOper();
        if (ch == '/') {
            take_s();
            char next = peek_s();
            if (next == '/') return scanSingleLineComment(true);
            else if (next == '*') return scanComment(true);
            else return div();
        }
        makeSure(false, "not an operator");
    }
    }
    // suppress warning, impossible to reach
    return Token<void*>();
}

void Lexer::skipBlank() {
    if (scanner->peek() == nullptr) {
        if (eof()) throw std::out_of_range("eof");
        throw std::runtime_error("skipBlank");
    }
    scanner->drop();
}

Token<void*> Lexer::plus() {
    std::string result;
    std::string value;
    makeSure(peek_s() == '+', "plus");
    result.push_back(take_s());
    switch (peek_s()) {
    case '+': value = "plus plus"; result.push_back(take_s()); break;
    case '=': value = "plus equal"; result.push_back(take_s()); break;
    default: value = "plus";
    }
    return Token<void*>{result, Terminal::OPERATOR, nullptr, value};
}

Token<void*> Lexer::minus() {
    std::string result;
    std::string value;
    makeSure(peek_s() == '-', "minus");
    result.push_back(take_s());
    switch (peek_s()) {
    case '-': value = "minus minus"; result.push_back(take_s()); break;
    case '=': value = "minus equal"; result.push_back(take_s()); break;
    case '>': value = "point to"; result.push_back(take_s()); break;
    default: value = "minus";
    }
    return Token<void*>{result, Terminal::OPERATOR, nullptr, value};
}

Token<void*> Lexer::mod() {
    std::string result;
    makeSure(peek_s() == '%', "mod");
    result.push_back(take_s());
    if (peek_s() == '=') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "mod equal"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "mod"};
    }
}

Token<void*> Lexer::multiple() {
    std::string result;
    makeSure(peek_s() == '*', "asterisk");
    result.push_back(take_s());
    if (peek_s() == '=') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "multiple equal"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "dereference/multiple"};
    }
}

Token<void*> Lexer::div() {
    // assume that a "/" is read already
    std::string result("/");
    if (peek_s() == '=') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "div equal"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "div"};
    }
}

Token<void*> Lexer::ref() {
    std::string result;
    makeSure(peek_s() == '&', "ref");
    result.push_back(take_s());
    if (peek_s() == '&') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "and"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "ref"};
    }
}

Token<void*> Lexer::bitwiseOr() {
    std::string result;
    makeSure(peek_s() == '|', "bitwiseOr");
    result.push_back(take_s());
    if (peek_s() == '|') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "or"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "bitwise or"};
    }
}

Token<void*> Lexer::exclam() {
    std::string result;
    makeSure(peek_s() == '!', "exclam");
    result.push_back(take_s());
    if (peek_s() == '=') {
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "not equal"};
    } else {
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "not"};
    }
}

Token<void*> Lexer::singleOper() {  // dot, not, xor, comma
    char ch = peek_s();
    static const std::string sOper = ".~^,";
    makeSure(sOper.find(ch) != sOper.npos, "singleOper");
    take_s();
    switch (ch) {
    case '.': return Token<void*>{".", Terminal::OPERATOR, nullptr, "dot"};
    case '~': return Token<void*>{"~", Terminal::OPERATOR, nullptr, "not"};
    case '^': return Token<void*>{"^", Terminal::OPERATOR, nullptr, "xor"};
    case ',': return Token<void*>{",", Terminal::OPERATOR, nullptr, "comma"};
    default: throw std::runtime_error("impossible");
    }
}

Token<void*> Lexer::lessThan() {
    std::string result;
    makeSure(peek_s() == '<', "lessThan");
    result.push_back(take_s());
    switch (peek_s()) {
    case '=':
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "lessEqual than"};
    case '<': {
        result.push_back(take_s());
        if (peek_s() == '=') {
            result.push_back(take_s());
            return Token<void*>{result, Terminal::OPERATOR, nullptr, "shift left equal"};
        } else {
            return Token<void*>{result, Terminal::OPERATOR, nullptr, "shift left"};
        }
    }
    default: return Token<void*>{"<", Terminal::OPERATOR, nullptr, "less than"};
    }
}

Token<void*> Lexer::greaterThan() {
    std::string result;
    makeSure(peek_s() == '>', "greaterThan");
    result.push_back(take_s());
    switch (peek_s()) {
    case '=':
        result.push_back(take_s());
        return Token<void*>{result, Terminal::OPERATOR, nullptr, "greaterEqual than"};
    case '>': {
        result.push_back(take_s());
        if (peek_s() == '=') {
            result.push_back(take_s());
            return Token<void*>{result, Terminal::OPERATOR, nullptr, "shift right equal"};
        } else {
            return Token<void*>{result, Terminal::OPERATOR, nullptr, "shift right"};
        }
    }
    default: return Token<void*>{">", Terminal::OPERATOR, nullptr, "greater than"};
    }
}

Token<void*> Lexer::equal() {
    makeSure(peek_s() == '=', "equal");
    take_s();
    if (peek_s() == '=') {
        take_s();
        return Token<void*>{"==", Terminal::OPERATOR, nullptr, "equal"};
    }
    else return Token<void*>{"=", Terminal::OPERATOR, nullptr, "assign"};
}

using TH = TokenHandler;

std::pair<std::string, std::string> Lexer::getNext() noexcept(false) {
    static const std::string blank = " \t\n";
    static const std::string splitter = "(){}[];:?";
    static const std::string operatorBegin = "+-*%&|!<>=/.~^,";
    char ch = peek_s();
    while (blank.find(ch) != blank.npos) { // is blank
        skipBlank();
        return getNext();
    }
    if (std::isalpha(ch)) return TH::readToken(scanIdentifier());
    if (std::isdigit(ch)) return TH::readToken(scanNumber());
    if (ch == '\"') return TH::readToken(scanString());
    if (ch == '\'') return TH::readToken(scanChar());
    if (splitter.find(ch) != splitter.npos) { // is splitter
        return TH::readToken(scanSplitter());
    }
    if (ch == '#') return TH::readToken(scanDirective());
    if (operatorBegin.find(ch) != operatorBegin.npos) { // is operator or comment
        return TH::readToken(scanOperator());
    }
    else {
        take_s();
        return TH::readToken(Token<void*>{std::string(1, ch), Terminal::OTHER, nullptr, "unknown token"});
    }
}
