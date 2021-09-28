#ifndef TALKMANAGER_H
#define TALKMANAGER_H

#include <QJsonObject>
#include <QJsonArray>

#include <tokencollection.h>

class TalkManager: public QObject
{
    Q_OBJECT
public:
    TalkManager(const QString& tagRegexStr, const QString& htmlRegexStr);
    ~TalkManager();

    bool LoadTalks(QJsonObject* json);
    void PrintTalksList();
    QString GetTalk(int idx);
    TokenCollection MakeTokens(const QString& talk);
    QString PreprocessTalk(const QString& talk);
    void Parse(TokenCollection& tc, const QString& str, const QRegularExpression& regex);


    QStringList GetCurrentTokensList();
    QRegularExpression GetTagRegex();

signals:
    void TokenReadySignal(const QString& token);
public slots:
    void GetNextToken();

private:
    QStringList talksList;
    QStringList currentTokensList;
    int tokenCursor;
    QRegularExpression tagRegex, htmlRegex;
};
#endif // TALKMANAGER_H
