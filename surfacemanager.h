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

private:
    QList<Surface> surfaceList;
};

#endif // SURFACEMANAGER_H
