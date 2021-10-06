#include "surface.h"

Surface::Surface(unsigned int _id, const QString &_image, const QString &_name)
    : id(_id),
      image(_image),
      name(_name),
      animations(QMap<unsigned int, Animation*>()),
      namedAnimations(QMap<QString, Animation*>())
{

}

Surface::~Surface()
{
    for (auto &it: animations.values())
        delete it;
}

QString Surface::PrintData()
{
    auto str = QString(QString::number(id) + "\t" + image + "\t" + name + "\n");
    auto animcount = animations.keys().length();
    str.append(QString::number(animcount) + " animations\n");

    if (animcount > 0) {
        str.append("\t\tId\tFrequency\n");
        for (auto &it: animations.values()) {
            str.append("\t\t" + it->PrintData() + "\n");
        }
    }

    return str;
}

unsigned int Surface::GetId() const
{
    return id;
}

QString Surface::GetImage() const
{
    return image;
}

QString Surface::GetName() const
{
    return name;
}

bool Surface::HasName() const
{
    return name != "";
}

Animation *Surface::AddAnimation(unsigned int _id, const QString& _name, Frequency _frequency)
{
    auto a = new Animation(_id, _name, _frequency);
    animations.insert(_id, a);

    if (a->HasName()) {
        namedAnimations.insert(_name, a);
    }

    return a;
}

Animation *Surface::GetAnimation(unsigned int _id)
{
    return animations.value(_id, nullptr);
}

Animation *Surface::GetAnimation(const QString &_name)
{
    return namedAnimations.value(_name, nullptr);
}
