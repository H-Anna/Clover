#include "frame.h"

Frame::Frame(int _id, const QString &_image, DrawMethod _drawMethod):
    id(_id),
    image(_image),
    drawMethod(_drawMethod)
{

}

int Frame::GetId() const
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
