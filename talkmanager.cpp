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
        qDebug() << "ERROR - TalkManager - Talks couldn't be loaded!";
        return false;
    }

    for (int i = 0; i < talksArray.count(); i++) {
        talksList.append(talksArray.at(i).toString());
    }

    return true;
}

void TalkManager::PrintTalksList()
{
    qDebug() << "INFO - TalkManager";

    if (talksList.count() > 0) {
        qDebug() << "Talks loaded:" << talksList.count();

        for (auto &it: talksList) {
            qDebug().noquote() << it;
        }
    } else {
        qDebug() << "No talks loaded.";
    }

}

QString TalkManager::GetTalk(int idx)
{
    if (talksList.length() == 0) {
        qDebug() << "WARNING - TalkManager - Empty talks list, empty string returned.";
        return "";
    }

    if (idx < talksList.length())
        return talksList.at(idx);

    qDebug().nospace() << "WARNING - TalkManager - No talk at index " << idx << ", last in list returned.";
    return talksList.at(talksList.length()-1);
}

QStringList TalkManager::Parse(const QString &talk)
{
    QStringList parsed;
    int cursorPos = 0;

    ///TODO: create a regex that has more characters available but doesn't capture HTML doctype and comment
    QRegularExpression regex(R"(<![\s\w\[\]]+>)");
    auto iter = regex.globalMatch(talk);

    ///Separate tags and pieces of text into tokens
    while (iter.hasNext()) {

        ///Setup variables, get next match
        auto match = iter.next();
        auto matchStr = match.captured();
        QString leadText, tag;

        ///separate text leading up to tag, and captured tag
        leadText = talk.mid(cursorPos, match.capturedStart() - cursorPos);
        tag = matchStr;

        ///Append to list
        if (!leadText.isEmpty())
            parsed.append(leadText);

        parsed.append(tag);
        cursorPos = match.capturedEnd();
    }



    return parsed;
}

