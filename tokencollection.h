#ifndef TOKENCOLLECTION_H
#define TOKENCOLLECTION_H

#include <QMap>
#include <QDebug>

#include <token.h>

class TokenCollection
{
public:
    TokenCollection();

    bool HasHtml();
    void append(const QString& token, Token::TokenType type, const QStringList& params = QStringList());

    Token GetNextToken();

private:

    bool hasHtml;
    int tokenCursor;
    QList<Token> tokenList;
};

#endif // TOKENCOLLECTION_H
