#ifndef TALKPARSER_H
#define TALKPARSER_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class TalkParser
{
public:
    TalkParser();

    static QStringList Parse(const QString& talk);
};

#endif // TALKPARSER_H
