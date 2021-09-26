#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QStringList>

class Token
{
public:
    enum TokenType {
        HtmlTag,
        CommandTag,
        PlainText,
        END
    };

    Token();
    Token(const QString& _contents, TokenType _type, QStringList _params);

    QString getContents() const;
    TokenType getType() const;
    QStringList getParams() const;

private:
    QString contents;
    TokenType type;
    QStringList params;
};

#endif // TOKEN_H
