#include "talkmanager.h"

TalkManager::TalkManager()
{

}

TalkManager::~TalkManager()
{
}

bool TalkManager::LoadTalks(QJsonObject *json)
{
    QJsonArray talksArray = json->value("talks").toArray();

    if (talksArray.empty()) {
        std::cout << "ERROR - TalkManager - Talks couldn't be loaded!" << std::endl;
        return false;
    }

    for (int i = 0; i < talksArray.count(); i++) {
        talksList.append(talksArray.at(i).toString());
    }

    return true;
}

void TalkManager::PrintTalksList()
{
    std::cout << "INFO - TalkManager" << std::endl;

    if (talksList.count() > 0) {
        std::cout << "Talks loaded: " << talksList.count() << std::endl;

        for (auto &it: talksList) {
            std::cout << it.toStdString() << std::endl;
        }
    } else {
        std::cout << "No talks loaded." << std::endl;
    }

}

