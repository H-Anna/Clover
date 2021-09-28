#include "talkmanager.h"

TalkManager::TalkManager(const QString &regexStr, const QString &htmlRegexStr)
    :
    currentTokensList(QStringList()),
    tokenCursor(0)
{
    tagRegex.setPattern(regexStr);
    htmlRegex.setPattern(htmlRegexStr);
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

TokenCollection TalkManager::MakeTokens(const QString &talk)
{
    auto tokens = new TokenCollection();

    /// Preprocessing talks, such as replacing &quot with quotation marks

    auto _talk = PreprocessTalk(talk);

    Parse(*tokens, _talk, tagRegex);

    /// If you want to post-process tokens, call tokens->Finalize() here

    return *tokens;

}

QString TalkManager::PreprocessTalk(const QString &talk)
{
    QString _t = talk;
    _t.replace("&quot", "\"");

    return _t;
}

void TalkManager::Parse(TokenCollection &tc, const QString &str, const QRegularExpression &regex)
{
    QStringList parsed;
    int cursorPos = 0;

    auto iter = regex.globalMatch(str);

    /// Separate tags and pieces of text into tokens

    while (iter.hasNext()) {

        /// Setup variables, get next match

        auto match = iter.next();
        QString leadText, tag;
        QStringList params;

        /// -------------------------------------
        /// PARSING / SAVING LEADING TEXT
        /// -------------------------------------

        /// Separate text leading up to tag, and captured tag

        leadText = str.mid(cursorPos, match.capturedStart() - cursorPos);

        /// Append to list
        if (!leadText.isEmpty()) {

            /// If HTML tags are being parsed, then what we have is most definitely plaintext.
            /// Can't be processed any further -> append.
            if (regex == htmlRegex) {
                tc.append(leadText, Token::PlainText);
            }

            /// If Command tags are being parsed, leadText may contain HTML. Parse again.
            /// The "if" above ensures that the Parse function that parses HTML tags will not recurse.
            else {
                Parse(tc, leadText, htmlRegex);
            }
        }

        /// -------------------------------------
        /// SAVING TAG
        /// -------------------------------------

        /// Take tag (key in map) and see if there's any parameters
        if (regex == htmlRegex) {

            tag = match.captured();

        } else {

            tag = match.captured(1);
            auto _p = match.captured(2);

            if (!_p.isNull()) {
                auto _list = _p.split(',', Qt::SkipEmptyParts);

                for (auto &it: _list)
                    it = it.trimmed();

                params = _list;
            }
        }

        ///Mark tag type correctly.
        tc.append(tag, regex == htmlRegex ? Token::HtmlTag : Token::CommandTag, params);

        cursorPos = match.capturedEnd();
    }

    ///If there is some text left, parse it the same way as leadText above.

    if (cursorPos < str.length()) {
        auto remainderText = str.mid(cursorPos, str.length() - cursorPos);

        if (!remainderText.isEmpty()) {

            if (regex == htmlRegex) {
                tc.append(remainderText, Token::PlainText);
            }
            else {
                Parse(tc, remainderText, htmlRegex);
            }
        }
    }

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

