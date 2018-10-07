#ifndef LEXER_H
#define LEXER_H

#include <stdexcept>
#include <memory>

class AbstractScanner;

enum class Terminal {
    ID, KEYWORD, NUM, STR, COMMENT, SPLITTER, OPERATOR, DIRECTIVE, OTHER
};

enum class NumType { Integer, Floating};

template <typename Attr>
struct Token {
    std::string lexeme;
    Terminal terminal;
    Attr value;
    std::string description;
    Token() {}
    Token(std::string const& aLexeme, Terminal aTerminal, Attr aValue, std::string const& aDescription): lexeme(aLexeme),
        terminal(aTerminal), value(aValue), description(aDescription) {}
    Token(Token<Attr> const& other): lexeme(other.lexeme), terminal(other.terminal),
        value(other.value) {}
};

class Lexer {
    std::shared_ptr<AbstractScanner> scanner = nullptr;
    char take_s() noexcept(false);
    char peek_s() noexcept(false);
    void makeSure(bool condition, std::string const& msg) {
        if (!condition) throw std::runtime_error(msg + ": cannot make sure");
    }
    Token<void*> plus() noexcept(false);
    Token<void*> minus() noexcept(false);
    Token<void*> multiple() noexcept(false);
    Token<void*> mod() noexcept(false);
    Token<void*> div() noexcept(false);
    Token<void*> ref() noexcept(false); // bitwise and
    Token<void*> bitwiseOr() noexcept(false);
    Token<void*> exclam() noexcept(false);
    Token<void*> singleOper() noexcept(false);
    Token<void*> lessThan() noexcept(false);
    Token<void*> greaterThan() noexcept(false);
    Token<void*> equal() noexcept(false);

public:
    Token<void*> scanIdentifier() noexcept(false);
    Token<NumType> scanNumber() noexcept(false);
    Token<void*> scanChar() noexcept(false);
    Token<void*> scanString() noexcept(false);
    Token<void*> scanComment(bool alreadyReadFront) noexcept(false);
    Token<void*> scanSingleLineComment(bool alreadyReadFront) noexcept(false);
    Token<void*> scanSplitter() noexcept(false);
    Token<std::string> scanDirective() noexcept(false);
    Token<void*> scanOperator() noexcept(false);
    void skipBlank();
    Lexer(std::shared_ptr<AbstractScanner> scanner);
    void setScanner(std::shared_ptr<AbstractScanner> scanner);
    bool eof();
    std::pair<std::string, std::string> getNext() noexcept(false);
};

#endif // LEXER_H
