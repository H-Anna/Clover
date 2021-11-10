#include "hotspotwidget.h"

HotspotWidget::HotspotWidget(VariableStore* varStore, QWidget *parent):
    QWidget(parent),
    affection(0),
    clicks(0)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMouseTracking(true);
    setAutoFillBackground(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    setPalette(p);

    /// TODO: connect a TalkManager signal here

    connect(this, SIGNAL(hotspotTalkSignal(QString,QString)),
            varStore->GetMember("TalkManager"), SLOT(AnchorTalk(QString,QString)));

    showMaximized();
}

void HotspotWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << QString("Mouse entered");
    affection++;
    if (affection > 500) {
        emit hotspotTalkSignal("topic", "headpat");
        affection = 0;
    }

}

void HotspotWidget::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << QString("Pressed %1 mouse").arg(event->button());
    clicks++;
    if (clicks > 3) {
        emit hotspotTalkSignal("topic", "headclick");
        clicks = 0;
    }

}
