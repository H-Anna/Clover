#include "surface.h"

Surface::Surface(unsigned int _id, const QString &_image, const QString &_alias)
    : id(_id), image(_image), alias(_alias)
{

}

QString Surface::PrintData()
{
    return QString(QString::number(id) + "\t" + image + "\t" + alias);
}
