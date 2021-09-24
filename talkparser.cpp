#include "talkparser.h"

TalkParser::TalkParser()
{

}

QStringList TalkParser::Parse(const QString& talk)
{
    QStringList parsed;
    int cursorPos = 0;

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
