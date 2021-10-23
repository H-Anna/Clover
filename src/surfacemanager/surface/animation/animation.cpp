#include "animation.h"

Animation::Animation(int _id, QString _name, Frequency _frequency, unsigned int _layer):
    id(_id),
    name(_name),
    frequency(_frequency),
    layer(_layer),
    frameCursor(0),
    frames(QVector<Frame*>())
{

}

Animation::~Animation()
{
    while (!frames.isEmpty()) {
        delete frames.takeLast();
    }
}

QString Animation::PrintData()
{
    auto str = QString("%1\t%2\n%3 frames\n").arg(QString::number(id),
                                                  QMetaEnum::fromType<Frequency>().valueToKey(frequency),
                                                  QString::number(frames.length()));

    auto framecount = frames.length();
    str.append(QString("%1 frames\n").arg(framecount));

    for (auto &it: frames) {
        str.append(QString("\t\t%1\n").arg(it->PrintData()));
    }

    return str;
}

unsigned int Animation::GetId() const
{
    return id;
}

const QString &Animation::GetName() const
{
    return name;
}

bool Animation::HasName() const
{
    return name != "";
}

QVector<Frame *> Animation::GetFrames() const
{
    return frames;
}

Animation::Frequency Animation::GetFrequency() const
{
    return frequency;
}

unsigned int Animation::GetLayer() const
{
    return layer;
}

void Animation::AddFrame(const QString &_image, Frame::DrawMethod _drawMethod, unsigned int _ms)
{
    unsigned int _id = frames.length();
    frames.append(new Frame(_id, _image, _drawMethod, _ms));
}

Frame *Animation::GetNextFrame()
{
    if (frames.isEmpty())
        return nullptr;

    if (frameCursor >= frames.length()) {

        /// TODO: whats the difference between Loop and Always? I can't remember.
        /// Maybe I wanted to create Looping animations that play forever, and
        /// make Always animations oneshots that play when you enter the surface?

        switch (frequency) {
        case Frequency::Loop:
        case Frequency::Always: {
            frameCursor -= frames.length();

            return frames.at(frameCursor++);
        }
        case Frequency::Never: {
            return nullptr;
        }
        default:
            return nullptr;
        }

    } else {
        return frames.at(frameCursor++);
    }
}


