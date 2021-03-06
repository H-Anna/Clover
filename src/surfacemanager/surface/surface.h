#ifndef SURFACE_H
#define SURFACE_H

#include <animation.h>
#include <hotspot.h>

class Surface
{
public:
    Surface(unsigned int _id, const QString& _name = "");
    ~Surface();

    QString PrintData();

    unsigned int GetId() const;
    QVector<QString> GetElements() const;
    QString GetName() const;
    bool HasName() const;

    void AddElement(const QString& img);

    Animation* AddAnimation(unsigned int _id, const QString &_name, Animation::Frequency _frequency, unsigned int _layer);
    Animation* GetAnimation(unsigned int _id) const;
    Animation* GetAnimation(const QString& _name) const;
    QVector<Animation*> GetAnimations(Animation::Frequency f) const;

    void AddHotspot(const QString &_name, int TLX, int TLY, int BRX, int BRY, Qt::CursorShape _cursor);
    Hotspot* GetHotspot(const QString& name) const;
    QVector<Hotspot*> GetHotspots() const;

private:
    unsigned int id;
    QVector<QString> elements;
    QString name;

    QMap<unsigned int, Animation*> animations;
    QMap<QString, Animation*> namedAnimations;

    QMap<QString, Hotspot*> hotspots;
};

#endif // SURFACE_H
