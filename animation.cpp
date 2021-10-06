#include "animation.h"

Animation::Animation(int _id, QString _name, Frequency _frequency):
    id(_id),
    name(_name),
    frequency(_frequency),
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
    auto str = QString(QString::number(id) + "\t" + EnumConverter::GetFrequency(frequency) + "\n");
    auto framecount = frames.length();
    str.append(QString::number(framecount) + " frames\n");

    for (auto &it: frames) {
        str.append("\t\t" + it->PrintData() + "\n");
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

Frequency Animation::GetFrequency() const
{
    return frequency;
}

void Animation::AddFrame(const QString &_image, DrawMethod _drawMethod, unsigned int _ms)
{
    unsigned int _id = frames.length();
    frames.append(new Frame(_id, _image, _drawMethod, _ms));
}

Frame *Animation::GetNextFrame()
{
    if (frames.isEmpty())
        return nullptr;

    if (frameCursor >= frames.length()) {

        switch (frequency) {
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
