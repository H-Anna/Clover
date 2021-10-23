#include "surface.h"

Surface::Surface(unsigned int _id, const QString &_name):
    id(_id),
    name(_name),
    animations(QMap<unsigned int, Animation*>()),
    namedAnimations(QMap<QString, Animation*>())
{

}

Surface::~Surface()
{
    QMapIterator a(animations);
    while (a.hasNext()) {
        a.next();
        delete a.value();
    }

    QMapIterator h(hotspots);
    while (h.hasNext()) {
        h.next();
        delete h.value();
    }
}

QString Surface::PrintData()
{
    auto str = QString(QString::number(id) + "\t" + "\t" + name + "\n");
    for (auto &it: elements) {
        str.append(it + "\n");
    }
    auto animcount = animations.size();
    str.append(QString::number(animcount) + " animations\n");
    str.append(QString("%1 animations\n").arg(animcount));

    if (animcount > 0) {
        str.append("\t\tId\tFrequency\n");

        QMapIterator a(animations);
        while (a.hasNext()) {
            a.next();
            str.append("\t\t" + a.value()->PrintData() + "\n");
        }
    }

    return str;
}

unsigned int Surface::GetId() const
{
    return id;
}

QVector<QString> Surface::GetElements() const
{
    return elements;
}

QString Surface::GetName() const
{
    return name;
}

bool Surface::HasName() const
{
    return name != "";
}

void Surface::AddElement(const QString &img)
{
    elements.append(img);
}

Animation *Surface::AddAnimation(unsigned int _id, const QString& _name, Animation::Frequency _frequency, unsigned int _layer)
{
    auto a = new Animation(_id, _name, _frequency, _layer);
    animations.insert(_id, a);

    if (a->HasName()) {
        namedAnimations.insert(_name, a);
    }

    return a;
}

QVector<Animation *> Surface::GetAnimations(Animation::Frequency f) const
{
    QVector<Animation *> anims = QVector<Animation*>();
    for (auto &it: animations) {
        if (it->GetFrequency() == f)
            anims.append(it);
    }
    return anims;
}

void Surface::AddHotspot(const QString &_name, int TLX, int TLY, int BRX, int BRY, Qt::CursorShape _cursor)
{
    hotspots.insert(_name, new Hotspot(_name, TLX, TLY, BRX, BRY, _cursor));
}

Hotspot *Surface::GetHotspot(const QString &name) const
{
    return hotspots.value(name);
}

QVector<Hotspot *> Surface::GetHotspots() const
{
    QVector<Hotspot *> hs = QVector<Hotspot *>();
    for (auto &it: hotspots) {
        hs.append(it);
    }
    return hs;
}

Animation *Surface::GetAnimation(unsigned int _id) const
{
    return animations.value(_id, nullptr);
}

Animation *Surface::GetAnimation(const QString &_name) const
{
    return namedAnimations.value(_name, nullptr);
}
