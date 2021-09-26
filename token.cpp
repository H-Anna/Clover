#include "token.h"

Token::Token():
    contents(QString()),
    type(TokenType::END),
    params()
{

}

Token::Token(const QString &_contents, TokenType _type, QStringList _params = QStringList()):
    contents(_contents),
    type(_type),
    params(_params)
{

}

QString Token::getContents() const
{
    return contents;
}

Token::TokenType Token::getType() const
{
    return type;
}

QStringList Token::getParams() const
{
    return params;
}

