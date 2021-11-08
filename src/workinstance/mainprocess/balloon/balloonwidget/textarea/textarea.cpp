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

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);

    connect(this, &QTextBrowser::anchorClicked,
            this, &TextArea::EvaluateAnchor);

    connect(this, SIGNAL(openUrlSignal(QUrl)),
            varStore->GetMember("MainProcess"), SLOT(OpenUrl(QUrl)));

    connect(this, SIGNAL(anchorTalkSignal(QString)),
            varStore->GetMember("TalkManager"), SLOT(AnchorTalk(QString)));

    show();
}

void TextArea::EvaluateAnchor(QUrl url)
{
    if (url.scheme() == "http" || url.scheme() == "https") {
        emit openUrlSignal(url);
    } else if (url.scheme() == "topic") {
        emit anchorTalkSignal(url.path());
    }
}
