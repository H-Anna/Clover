#ifndef TALKMANAGER_H
#define TALKMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

#include <tokencollection.h>

class TalkManager: public QObject
{
    Q_OBJECT
public:
    TalkManager(const QString& tagRegexStr, const QString& htmlRegexStr);
    ~TalkManager();

    bool LoadTalks(QJsonObject* json);
    bool LoadAnchors(QJsonObject* json);

    TokenCollection MakeTokens(const QString& talk);
    QString PreprocessTalk(const QString& talk);
    void Parse(TokenCollection& tc, const QString& str, const QRegularExpression& regex);

public slots:
    void RandomTalk();
    void IndexedTalk(int idx);
    void AnchorTalk(QString anchor);

signals:
    void tokensReadySignal(TokenCollection tc);

private:
    QVector<QString> talksList;
    QMap<QString, QString> anchorTalks;
    unsigned int tokenCursor;
    QRegularExpression tagRegex, htmlRegex;
};
#endif // TALKMANAGER_H
