#include "token.h"

Token::Token():
    contents(QString()),
    type(TokenType::End),
    params()
{

}

Token::Token(const QString &_contents, TokenType _type, QStringList _params):
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

