#include "surface.h"

Surface::Surface(unsigned int _id, const QString &_image, const QString &_name)
    : id(_id),
      image(_image),
      name(_name),
      animationIDMap(QMap<unsigned int, Animation*>()),
      namedAnimations(QMap<QString, Animation*>())
{

}

QString Surface::PrintData()
{
    auto str = QString(QString::number(id) + "\t" + image + "\t" + name + "\n");
    auto animcount = animationIDMap.keys().length();
    str.append(QString::number(animcount) + " animations\n");

    if (animcount > 0) {
        str.append("\t\tId\tFrequency\n");
        for (auto &it: animationIDMap.values()) {
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
    animationIDMap.insert(_id, a);

    if (a->HasName()) {
        namedAnimations.insert(_name, a);
    }

    return a;
}

Animation *Surface::GetAnimation(unsigned int _id)
{
    return animationIDMap.value(_id, nullptr);
}

Animation *Surface::GetAnimation(const QString &_name)
{
    return namedAnimations.value(_name, nullptr);
}
