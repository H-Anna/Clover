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

QString Token::GetContents() const
{
    return contents;
}

Token::TokenType Token::GetType() const
{
    return type;
}

QString Token::GetTypeAsString() const
{
    switch (type) {

    case HtmlTag: {
        return "HtmlTag";
    }
    case CommandTag: {
        return "CommandTag";
    }
    case PlainText: {
        return "PlainText";
    }
    case End: {
        return "End";
    }
    }

    return "NULL";
}

QStringList Token::GetParams() const
{
    return params;
}

