#ifndef SURFACE_H
#define SURFACE_H

#include <animation.h>

class Surface
{
public:
    Surface(unsigned int _id, const QString& _image, const QString& _alias = "");

    QString PrintData();

    unsigned int GetId() const;
    QString GetImage() const;
    QString GetAlias() const;
    bool HasAlias() const;

    Animation* AddAnimation(unsigned int _id, DrawMethod _drawMethod);

private:
    unsigned int id;
    QString image;
    QString alias;

    QMap<int, Animation*> animationIDMap;
};

#endif // SURFACE_H
