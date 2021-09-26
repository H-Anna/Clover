#include "talkmanager.h"

TalkManager::TalkManager(QString regexStr)
{
    currentTokensList = QStringList();
    tokenCursor = 0;

    tagRegex.setPattern(regexStr);
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

void TalkManager::Parse(const QString &talk)
{
    QStringList parsed;
    int cursorPos = 0;

    auto iter = tagRegex.globalMatch(talk);

    /// Separate tags and pieces of text into tokens

    while (iter.hasNext()) {

        /// Setup variables, get next match

        auto match = iter.next();
        auto matchStr = match.captured();
        QString leadText, tag;

        /// Separate text leading up to tag, and captured tag

        leadText = talk.mid(cursorPos, match.capturedStart() - cursorPos);
        tag = matchStr;

        /// Append to list

        if (!leadText.isEmpty())
            parsed.append(leadText);

        parsed.append(tag);
        cursorPos = match.capturedEnd();
    }

    if (cursorPos < talk.length())
        parsed.append(talk.mid(cursorPos, talk.length() - cursorPos));

    currentTokensList = parsed;
    tokenCursor = 0;
}

void TalkManager::GetNextToken()
{
    if (tokenCursor < currentTokensList.length()) {
        emit TokenReadySignal(currentTokensList.at(tokenCursor++));
    } else {
        qDebug() << "INFO - TalkManager - All tokens have been passed.";
    }
}

QStringList TalkManager::GetCurrentTokensList()
{
    return currentTokensList;
}

QRegularExpression TalkManager::GetTagRegex()
{
    return tagRegex;
}

