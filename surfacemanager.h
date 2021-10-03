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

    void MakeSurface(QJsonObject& obj);
    void MakeAnimation(QJsonObject& obj, Surface& s);

    QString imagePath;

    QMap<unsigned int, Surface*> surfaceIDMap;
    QMap<QString, Surface*> surfaceAliasMap;

    QMap<unsigned int, Animation*> animationIDMap;

    const static inline QMap<QString,DrawMethod> drawMethodMap = {
        {"base", DrawMethod::Base},
        {"overlay", DrawMethod::Overlay},
        {"clip", DrawMethod::Clip},
        {"replace", DrawMethod::Replace}
    };
};

#endif // SURFACEMANAGER_H
