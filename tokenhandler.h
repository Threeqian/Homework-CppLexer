#ifndef TOKENHANDLER_H
#define TOKENHANDLER_H

#include <utility>
#include <string>
#include "lexer.h"

class TokenHandler
{
    TokenHandler() = delete;
public:
    template <typename Attr>
    static std::pair<std::string, std::string> readToken(Token<Attr> const& token) {
        return std::make_pair(token.lexeme, token.description);
    }
};

#endif // TOKENHANDLER_H
