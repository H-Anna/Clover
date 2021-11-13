#include "tokencollection.h"

TokenCollection::TokenCollection():
    tokenCursor(0)
{
    tokenList.clear();
}

void TokenCollection::prepend(const QString &token, Token::TokenType type, const QStringList &params)
{
    auto t = new Token(token, type, params);
    tokenList.prepend(t);
}

void TokenCollection::append(const QString &token, Token::TokenType type, const QStringList &params)
{
    auto t = new Token(token, type, params);
    tokenList.append(t);
}

void TokenCollection::replaceAt(unsigned int id, TokenCollection *tc)
{
    QList<Token*> post;
    while (tokenList.length() > id + 1) {
        post.prepend(tokenList.takeLast());
    }
    tokenList.removeLast();
    tokenList.append(tc->tokenList);
    tokenList.append(post);
}

unsigned int TokenCollection::indexOf(Token *t)
{
    return tokenList.indexOf(t);
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

bool TokenCollection::HasPool()
{
    return std::any_of(tokenList.cbegin(), tokenList.cend(),
                       [](Token* t){ return t->GetType() == Token::PoolTag; });
}

Token *TokenCollection::GetNextPool()
{
    for (auto &t: tokenList) {
        if (t->GetType() == Token::PoolTag) {
            return t;
        }
    }

    return nullptr;
}
