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

QString TalkManager::GetTalk(int idx)
{
    if (talksList.length() == 0) {
        std::cout << "WARNING - TalkManager - Empty talks list, empty string returned." << std::endl;
        return "";
    }

    if (idx < talksList.length())
        return talksList.at(idx);

    std::cout << "WARNING - TalkManager - No talk at index " << idx << ", last in list returned." << std::endl;
    return talksList.at(talksList.length()-1);
}

