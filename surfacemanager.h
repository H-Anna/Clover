#ifndef SURFACEMANAGER_H
#define SURFACEMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include <surface.h>
#include <ghost.h>

class SurfaceManager: public QObject
{
    Q_OBJECT;
public:
    SurfaceManager();
    ~SurfaceManager();

    bool LoadSurfaces(QJsonObject* json, const QString& imgPath);
    void PrintSurfaceList();
    Surface* GetSurface(unsigned int id);
    Surface* GetSurface(const QString& name);

    void ApplyGraphics(const QString& tag, QStringList params, Ghost& g);

    unsigned int GetLayerCount() const;

private slots:
    void Animate(Animation *a, Ghost& g);

private:
    void MakeSurface(QJsonObject& obj);
    void MakeAnimation(QJsonObject& obj, Surface& s);

    QString imagePath;
    unsigned int layerCount;

    QMap<unsigned int, Surface*> surfaces;
    QMap<QString, Surface*> namedSurfaces;

    QMap<Animation*, QTimer*> timers;
};

#endif // SURFACEMANAGER_H
