#ifndef TALKMANAGER_H
#define TALKMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>
#include <QRegularExpression>

#include <tokencollection.h>

class TalkManager: public QObject
{
    Q_OBJECT

    typedef QMap<QString, QList<QString>> TalkPool;

public:
//    TalkManager(const QString& tagRegexStr, const QString& htmlRegexStr, QString &_stylesheet);
    TalkManager(const QString& tagRegexStr, const QString& htmlRegexStr);
    ~TalkManager();

    bool LoadTalks(QJsonObject* json);
    bool LoadAnchors(QJsonObject* json);
    bool LoadKeyTalks(QJsonObject* json);
    bool LoadStringPools(QJsonObject* json);

    TokenCollection MakeTokens(const QString& talk);
    QString PreprocessTalk(const QString& talk);

public slots:
    void RandomTalk();
    void IndexedTalk(int idx);
    void AnchorTalk(QString scheme, QString anchor);

signals:
    void tokensReadySignal(TokenCollection tc);

private:
    void Parse(TokenCollection& tc, const QString& str, const QRegularExpression& regex);
    void ReplacePools(TokenCollection& tc);
    QString FromPool(QString key);

    QVector<QString> talksList;
    QMap<QString, QString> anchorTalks;
    QMap<QString, QString> keyTalks;
    QRegularExpression tagRegex, htmlRegex;
    TalkPool pools;
    //QString* stylesheet;
};
#endif // TALKMANAGER_H
