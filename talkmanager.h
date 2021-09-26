#ifndef TALKMANAGER_H
#define TALKMANAGER_H

#include <QJsonObject>
#include <QJsonArray>

class TalkManager: public QObject
{
    Q_OBJECT
public:
    TalkManager(QString regexStr);
    ~TalkManager();

    bool LoadTalks(QJsonObject* json);
    void PrintTalksList();
    QString GetTalk(int idx);
    void Parse(const QString& talk);

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
    QRegularExpression tagRegex;
};
#endif // TALKMANAGER_H
