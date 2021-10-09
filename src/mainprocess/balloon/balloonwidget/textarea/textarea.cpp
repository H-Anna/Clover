#include "textarea.h"

TextArea::TextArea(QWidget *parent):
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

    show();
}
