#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QStringList>
#include <QObject>

class Token: public QObject
{
    Q_OBJECT
public:
    enum TokenType {
        HtmlTag,
        CommandTag,
        PlainText,
        End
    };
    Q_ENUM(TokenType)

    Token();
    Token(const QString& _contents, TokenType _type, QStringList _params = QStringList());

    QString GetContents() const;
    TokenType GetType() const;
    QStringList GetParams() const;

private:
    QString contents;
    TokenType type;
    QStringList params;
};

#endif // TOKEN_H
