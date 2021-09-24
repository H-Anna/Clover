#ifndef TALKMANAGER_H
#define TALKMANAGER_H

#include <iostream>

#include <QJsonObject>
#include <QJsonArray>

class TalkManager
{
public:
    TalkManager();
    ~TalkManager();

    bool LoadTalks(QJsonObject* json);
    void PrintTalksList();
    QString GetTalk(int idx);

private:
    QStringList talksList;
};
#endif // TALKMANAGER_H
