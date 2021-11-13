#ifndef TOKENCOLLECTION_H
#define TOKENCOLLECTION_H

#include <QMap>
#include <QDebug>

#include <token.h>

class TokenCollection
{
public:
    TokenCollection();

    void prepend(const QString& token, Token::TokenType type, const QStringList& params = QStringList());
    void append(const QString& token, Token::TokenType type, const QStringList& params = QStringList());
    void replaceAt(unsigned int id, TokenCollection* tc);
    unsigned int indexOf(Token *t);

    const Token* GetNextToken();
    void Finalize();
    bool HasPool();
    Token* GetNextPool();

private:
    int tokenCursor;
    QList<Token*> tokenList;
};

#endif // TOKENCOLLECTION_H
