#include "animation.h"

Animation::Animation(int _id, DrawMethod _drawMethod):
    id(_id),
    drawMethod(_drawMethod)
{

}

int Animation::GetId() const
{
    return id;
}

QMap<int, Frame *> Animation::GetFrames() const
{
    return frameIDMap;
}

DrawMethod Animation::GetDrawMethod() const
{
    return drawMethod;
}

void Animation::AddFrame(int _id, const QString &_image, DrawMethod _drawMethod)
{
    frameIDMap.insert(_id, new Frame(_id, _image, _drawMethod));
}
