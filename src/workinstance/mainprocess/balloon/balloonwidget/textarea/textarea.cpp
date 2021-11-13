#include "textarea.h"

TextArea::TextArea(VariableStore *varStore, QWidget *parent):
    QTextBrowser(parent)
{
    setReadOnly(true);
    setAcceptRichText(true);
    setAttribute(Qt::WA_TranslucentBackground);
    setOpenLinks(false);
    setContextMenuPolicy(Qt::NoContextMenu);
    setFrameShape(QFrame::NoFrame);
    setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    setMouseTracking(false);

    QObject::setObjectName("myballoon");

    textHolder = new QPlainTextEdit(this);
    textHolder->hide();
    connect(textHolder, &QPlainTextEdit::textChanged,
            this, &TextArea::TextBrowserUpdate);

    connect(this, &QTextBrowser::anchorClicked,
            this, &TextArea::EvaluateAnchor);

    connect(this, SIGNAL(openUrlSignal(QUrl)),
            varStore->GetMember("MainProcess"), SLOT(OpenUrl(QUrl)));

    connect(this, SIGNAL(anchorTalkSignal(QString,QString)),
            varStore->GetMember("TalkManager"), SLOT(AnchorTalk(QString,QString)));

//    connect(this, SIGNAL(keyTalkSignal(QString)),
//            varStore->GetMember("TalkManager"), SLOT(KeyTalk(QString)));

    show();
}

TextArea::~TextArea()
{
    delete textHolder;
}

void TextArea::EvaluateAnchor(QUrl url)
{
    if (url.scheme() == "http" || url.scheme() == "https") {
        emit openUrlSignal(url);
    }
    else if (url.scheme() == "anchor" || url.scheme() == "key") {
        emit anchorTalkSignal(url.scheme(), url.path());
    }
//    else if (url.scheme() == "key") {
//        emit keyTalkSignal(url.path());
//    }
}

void TextArea::TextBrowserUpdate()
{
    setHtml(textHolder->toPlainText());
    moveCursor(QTextCursor::End);
}
