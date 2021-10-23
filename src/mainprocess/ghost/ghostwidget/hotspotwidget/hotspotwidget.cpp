#include "hotspotwidget.h"

HotspotWidget::HotspotWidget(QWidget *parent) : QWidget(parent)
{

}

void HotspotWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void HotspotWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << QString("Pressed %1 mouse").arg(event->button());
}
