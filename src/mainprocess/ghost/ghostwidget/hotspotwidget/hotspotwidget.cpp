#include "hotspotwidget.h"

HotspotWidget::HotspotWidget(QWidget *parent):
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMouseTracking(true);
    setAutoFillBackground(false);
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    setPalette(p);

    showMaximized();
}

void HotspotWidget::mouseMoveEvent(QMouseEvent *event)
{
    /// TODO: why does this only fire when the mouse button is down??
    qDebug() << QString("Mouse entered");
}

QSize HotspotWidget::sizeHint() const
{
    return QSize(1000,1000);
}

void HotspotWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << QString("Pressed %1 mouse").arg(event->button());
}
