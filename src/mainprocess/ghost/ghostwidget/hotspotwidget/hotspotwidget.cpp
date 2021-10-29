#include "hotspotwidget.h"

HotspotWidget::HotspotWidget(QWidget *parent):
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMouseTracking(true);
    setAutoFillBackground(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    setPalette(p);

    /// TODO: connect a TalkManager signal here

    //QObject* tm = VariableStore::GetMember("TalkManager");
//    connect(this, SIGNAL(),
//            tm, SLOT());

    showMaximized();
}

void HotspotWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << QString("Mouse entered");
}

void HotspotWidget::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << QString("Pressed %1 mouse").arg(event->button());
}
