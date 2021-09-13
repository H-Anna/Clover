#ifndef SURFACE_H
#define SURFACE_H

#include <QString>

class Surface
{
public:
    Surface(unsigned int _id, const QString& _image, const QString& _alias = "");;
//private:
    unsigned int id;
    QString image;
    QString alias;
};

#endif // SURFACE_H
