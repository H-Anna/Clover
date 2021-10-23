#include "tokencollection.h"

TokenCollection::TokenCollection():
    tokenCursor(0)
{
    tokenList.clear();
}

void TokenCollection::append(const QString &token, Token::TokenType type, const QStringList &params)
{
    auto t = new Token(token, type, params);
    tokenList.append(t);
}

const Token *TokenCollection::GetNextToken()
{
    if (tokenCursor >= tokenList.length()) {
        tokenCursor = 0;
        return new Token();
    }
    return tokenList.at(tokenCursor++);
}

void TokenCollection::Finalize()
{
    ///If you want to post-process your tokens (eg. discard certain ones) then do that here.
}
