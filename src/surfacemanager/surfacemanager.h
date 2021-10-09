#ifndef SURFACEMANAGER_H
#define SURFACEMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include <surface.h>
#include <balloonsurface.h>

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
    unsigned int GetLayerCount() const;

    bool LoadBalloons(QJsonObject *json, const QString &imgPath);

    void Initialize();

public slots:
    void ApplyGraphics(const QString& tag, QStringList params, Surface* currentSurface);

signals:
    void applyAnimationSignal(Animation* a, Frame* f);
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
