#ifndef SURFACEMANAGER_H
#define SURFACEMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include <surface.h>
#include <balloonsurface.h>

class SurfaceManager: public QObject
{
    Q_OBJECT
public:
    SurfaceManager();
    ~SurfaceManager();

    bool LoadSurfaces(QJsonObject* json, const QString& path);
    void PrintSurfaceList();
    Surface* GetSurface(unsigned int id);
    Surface* GetSurface(const QString& name);
    BalloonSurface* GetBalloonSurface(unsigned int id);
    unsigned int GetLayerCount() const;
    QVector<Surface*> GetDefaultSurfaces() const;
    QVector<BalloonSurface*> GetDefaultBalloons() const;

    bool LoadBalloons(QJsonObject *json, const QString &path);

    void Initialize();

public slots:
    void ApplyAnimation(QStringList params, Surface *currentSurface);
    void ApplySurface(QStringList params);
    void ApplyBalloon(QStringList params);
signals:
    void animateGhostSignal(Animation* a, Frame* f);
    void changeSurfaceSignal(Surface* s);
    void changeBalloonSignal(BalloonSurface* b);

private slots:
    void Animate(Animation *a);

private:
    void MakeSurface(QJsonObject& obj);
    void MakeAnimation(QJsonObject& obj, Surface& s);
    void MakeBalloonSurface(QJsonObject &obj);

    QString imagePath;
    unsigned int layerCount;

    QMap<unsigned int, Surface*> surfaces;
    QMap<QString, Surface*> namedSurfaces;

    QMap<unsigned int, BalloonSurface*> balloonSurfaces;

    QMap<Animation*, QTimer*> timers;

};

#endif // SURFACEMANAGER_H
