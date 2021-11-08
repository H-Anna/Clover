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
    return QString("%1\t%2\t%3\t%4 ms").arg(QString::number(id),
                                            image,
                                            QMetaEnum::fromType<Frame::DrawMethod>().valueToKey(drawMethod),
                                            QString::number(ms));
}

unsigned int Frame::GetId() const
{
    return id;
}

QString Frame::GetImage() const
{
    return image;
}

Frame::DrawMethod Frame::GetDrawMethod() const
{
    return drawMethod;
}

unsigned int Frame::GetMs() const
{
    return ms;
}
