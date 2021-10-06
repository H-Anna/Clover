#ifndef SURFACE_H
#define SURFACE_H

#include <QMap>

#include <animation.h>

class Surface
{
public:
    Surface(unsigned int _id, const QString& _image, const QString& _name = "");

    QString PrintData();

    unsigned int GetId() const;
    QString GetImage() const;
    QString GetName() const;
    bool HasName() const;

    Animation* AddAnimation(unsigned int _id, const QString &_name, Frequency _frequency);
    Animation* GetAnimation(unsigned int _id);
    Animation* GetAnimation(const QString& _name);

private:
    unsigned int id;
    QString image;
    QString name;

    QMap<unsigned int, Animation*> animationIDMap;
    QMap<QString, Animation*> namedAnimations;
};

#endif // SURFACE_H
