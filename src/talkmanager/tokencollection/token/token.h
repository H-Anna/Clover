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
        End
    };

    Token();
    Token(const QString& _contents, TokenType _type, QStringList _params = QStringList());

    QString GetContents() const;
    TokenType GetType() const;
    QString GetTypeAsString() const;
    QStringList GetParams() const;

private:
    QString contents;
    TokenType type;
    QStringList params;
};

#endif // TOKEN_H
