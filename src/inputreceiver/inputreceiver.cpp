#include "inputreceiver.h"

InputReceiver::InputReceiver(QWidget *parent)
{

}

void InputReceiver::keyPressEvent(QKeyEvent *event)
{
    qDebug() << QString("INFO - InputReceiver - Pressed %1 key").arg(event->text());
}
