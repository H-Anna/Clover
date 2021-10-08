#ifndef TOKENCOLLECTION_H
#define TOKENCOLLECTION_H

#include <QMap>
#include <QDebug>

#include <token.h>

class TokenCollection
{
public:
    TokenCollection();

    void append(const QString& token, Token::TokenType type, const QStringList& params = QStringList());

    Token GetNextToken();
    void Finalize();

private:
    int tokenCursor;
    QList<Token> tokenList;
};

#endif // TOKENCOLLECTION_H
