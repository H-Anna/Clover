#ifndef SURFACEMANAGER_H
#define SURFACEMANAGER_H

#include <QJsonObject>
#include <QJsonArray>

#include <surface.h>

class SurfaceManager
{
public:
    SurfaceManager();
    ~SurfaceManager();

    bool LoadSurfaces(QJsonObject* json, const QString& imgPath);
    void PrintSurfaceList();
    Surface* GetSurface(unsigned int id);
    Surface* GetSurface(const QString& alias);

private:
    //QList<Surface> surfaceList;

    QMap<unsigned int, Surface*> surfaceIDMap;
    QMap<QString, Surface*> surfaceAliasMap;
    QList<Surface*> surfaceList;
};

#endif // SURFACEMANAGER_H
