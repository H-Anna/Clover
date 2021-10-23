#include "hotspot.h"

HotSpot::HotSpot(QWidget *parent) : QWidget(parent)
{

}

void HotSpot::mouseMoveEvent(QMouseEvent *event)
{

}

void HotSpot::mousePressEvent(QMouseEvent *event)
{
    qDebug() << QString("Pressed %1 mouse").arg(event->button());
}
