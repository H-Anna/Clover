#include "tokencollection.h"

TokenCollection::TokenCollection():
    hasHtml(false),
    tokenCursor(0)
{
    tokenList.clear();
}

bool TokenCollection::HasHtml()
{
    return hasHtml;
}

void TokenCollection::append(const QString &token, Token::TokenType type, const QStringList &params)
{
    auto t = Token(token, type, params);
    tokenList.append(t);

    if (t.getType() == Token::HtmlTag)
        hasHtml = true;
}

Token TokenCollection::GetNextToken()
{
    if (tokenCursor >= tokenList.length()) {
        tokenCursor = 0;
        return Token();
    }
    return tokenList.at(tokenCursor++);
}

void TokenCollection::Finalize()
{
    ///If you want to post-process your tokens (eg. discard certain ones) then do that here.
}
