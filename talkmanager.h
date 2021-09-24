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

private:
    QStringList talksList;
};
#endif // TALKMANAGER_H
