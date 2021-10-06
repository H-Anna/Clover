#include "frame.h"

Frame::Frame(unsigned int _id, const QString &_image, DrawMethod _drawMethod, unsigned int _ms):
    id(_id),
    image(_image),
    drawMethod(_drawMethod),
    ms(_ms)
{

}

QString Frame::PrintData()
{
    return QString(QString::number(id) + "\t" + image + "\t" + EnumConverter::GetDrawMethod(drawMethod) + "\t" + QString::number(ms)+" ms");
}

unsigned int Frame::GetId() const
{
    return id;
}

QString Frame::GetImage() const
{
    return image;
}

DrawMethod Frame::GetDrawMethod() const
{
    return drawMethod;
}

unsigned int Frame::GetMs() const
{
    return ms;
}
