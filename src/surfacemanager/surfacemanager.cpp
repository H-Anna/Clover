#include "surfacemanager.h"

SurfaceManager::SurfaceManager()
{

}

SurfaceManager::~SurfaceManager()
{
    for (auto &it: surfaces) {
        delete it;
    }
    QMapIterator t(timers);
    while (t.hasNext()) {
        t.next();
        delete t.value();
    }
}

bool SurfaceManager::LoadBalloons(QJsonObject *json, const QString &path)
{
    /// Read JSON object, load contents into surfaceList

    imagePath = path;

    QJsonArray balloonArray = json->value("content").toArray();

    if (balloonArray.isEmpty())
        return false;

    for (int i = 0; i < balloonArray.count(); i++) {
        auto obj = balloonArray.at(i).toObject();
        MakeBalloonSurface(obj);
    }

    return true;
}

void SurfaceManager::Initialize()
{
    /// 0 is the default surface.

//    emit changeSurfaceSignal(surfaces.value(0));
//    emit changeBalloonSignal(balloonSurfaces.value(0));
}

bool SurfaceManager::LoadSurfaces(QJsonObject *json, const QString &path)
{
    /// Read JSON object, load contents into surfaceList

    imagePath = path;
    layerCount = json->value("layercount").toInt();
    QJsonArray surfaceArray = json->value("content").toArray();

    if (surfaceArray.isEmpty())
        return false;

    for (int i = 0; i < surfaceArray.count(); i++) {
        auto obj = surfaceArray.at(i).toObject();
        MakeSurface(obj);
    }

    return true;
}

void SurfaceManager::Animate(Animation* a)
{
    auto f = a->GetNextFrame();

    if (f == nullptr) {

        delete timers.value(a);
        timers.remove(a);

        return;
    }
    f->GetImage(), a->GetLayer(), f->GetDrawMethod();

    emit animateGhostSignal(a, f);

    if (f->GetMs() == 0) {

        a->Reset();

        if (timers.contains(a)) {
            timers.value(a)->stop();
        }

        return;
    }

    QTimer* timer;

    if (timers.contains(a)) {
        timer = timers.value(a);
    } else {
        timer = new QTimer(this);
        timer->callOnTimeout(this, [this, a](){ Animate(a); });
        timer->setSingleShot(true);
        timers[a] = timer;
    }

    timer->setInterval(f->GetMs());
    timer->start();
}

void SurfaceManager::ApplyAnimation(QStringList params, Surface *currentSurface) {

    QString str = params.at(0);
    bool canConvertToInt;
    str.toInt(&canConvertToInt);

    Surface* s = currentSurface;

    Animation* a = nullptr;
    if (canConvertToInt) {
        a = s->GetAnimation(str.toInt());
    } else {
        a = s->GetAnimation(str);
    }

    if (a == nullptr) {
        qDebug().noquote() << QString("WARNING - SurfaceManager - No animation found with param %1, skipping to next token.").arg(str);
        return;
    }

    Animate(a);
}

void SurfaceManager::ApplySurface(QStringList params) {

    QMapIterator t(timers);
    while (t.hasNext()) {
        t.next();
        t.key()->Reset();
        t.value()->stop();
        delete t.value();
    }
    timers.clear();

    QString str = params.at(0);
    bool canConvertToInt;
    str.toInt(&canConvertToInt);

    Surface* s;
    if (canConvertToInt) {
        s = GetSurface(str.toInt());
    } else {
        s = GetSurface(str);
    }

    if (s == nullptr) {
        qDebug().noquote() << QString("WARNING - SurfaceManager - No surface found with param %1, skipping to next token.").arg(str);
        return;
    }

    /// Apply surface

    emit changeSurfaceSignal(s);

    /// If it has animations that always play, play them.

    auto always = s->GetAnimations(Animation::Always);

    if (always.length() > 0) {

        for (auto &it: always) {
            Animate(it);
        }
    }
}

void SurfaceManager::ApplyBalloon(QStringList params) {

    QString str = params.at(0);
    bool canConvertToInt;
    str.toInt(&canConvertToInt);

    BalloonSurface* b;

    if (canConvertToInt) {
        b = GetBalloonSurface(str.toInt());
    } else {
        /// String fallback
        b = GetBalloonSurface(0);
    }

    if (b == nullptr) {
        qDebug().noquote() << QString("WARNING - SurfaceManager - No balloon surface found with param %1, skipping to next token.").arg(str);
        return;
    }

    /// Apply balloon

    emit changeBalloonSignal(b);
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    if (surfaces.count() > 0) {
        qDebug() << QString("Surfaces loaded: %1").arg(surfaces.count());
        qDebug() << "ID\tImage\tName";

        QMapIterator s(surfaces);
        while (s.hasNext()) {
            s.next();
            qDebug().noquote() << s.value()->PrintData();
        }

    } else {
        qDebug() << "No surfaces loaded.";
    }
}

Surface *SurfaceManager::GetSurface(unsigned int id)
{
    return surfaces.value(id, nullptr);
}

Surface* SurfaceManager::GetSurface(const QString &name)
{
    return namedSurfaces.value(name, nullptr);
}

BalloonSurface *SurfaceManager::GetBalloonSurface(unsigned int id)
{
    return balloonSurfaces.value(id, nullptr);
}

void SurfaceManager::MakeSurface(QJsonObject &obj)
{
    /// Make surface

    unsigned int id = obj.value("id").toInt();
    auto elements = obj.value("elements").toArray();

    QString name = obj.value("name").toString();

    auto s = new Surface(id, name);
    surfaces.insert(s->GetId(), s);
    if (s->HasName())
        namedSurfaces.insert(s->GetName(), s);

    for (auto it: elements) {
        s->AddElement(imagePath + it.toString());
    }

    /// Make animations

    QJsonArray animArray = obj.value("animations").toArray();
    if (!animArray.isEmpty()) {

        for (int i = 0; i < animArray.count(); i++) {
            auto obj = animArray.at(i).toObject();
            MakeAnimation(obj, *s);
        }

    }

    QJsonArray hotspotArray = obj.value("hotspots").toArray();
    if (!hotspotArray.isEmpty()) {

        for (int i = 0; i < hotspotArray.count(); i++) {

            auto obj = hotspotArray.at(i).toObject();

            auto name = obj.value("name").toString();
            auto area = obj.value("area").toArray();
            auto c = obj.value("cursor").toString();

            int cursor;
            bool ok;
            c.toInt(&ok);
            if (ok) {
                cursor = c.toInt();
            } else {
                cursor = QMetaEnum::fromType<Qt::CursorShape>().keyToValue(obj.value("cursor").toString().toStdString().c_str());
            }

            s->AddHotspot(name, area.at(0).toInt(), area.at(1).toInt(), area.at(2).toInt(), area.at(3).toInt(), Qt::CursorShape(cursor));
        }
    }
}

void SurfaceManager::MakeAnimation(QJsonObject &obj, Surface& s)
{
    /// If there are no frames, ignore animations

    QJsonArray framesArray = obj.value("frames").toArray();
    if (framesArray.isEmpty())
        return;

    /// Make animation & frames

    unsigned int id = obj.value("id").toInt();
    unsigned int layer = obj.value("layer").toInt(0);
    auto frequency = QMetaEnum::fromType<Animation::Frequency>().keyToValue(obj.value("frequency").toString().toStdString().c_str());
    QString name = obj.value("name").toString("");
    auto a = s.AddAnimation(id, name, Animation::Frequency(frequency), layer);

    for (int k = 0; k < framesArray.count(); k++) {

        /// Make a frame

        QJsonObject frame = framesArray.at(k).toObject();
        QString image = imagePath + frame.value("image").toString();
        auto drawMethod = QMetaEnum::fromType<Frame::DrawMethod>().keyToValue(frame.value("drawmethod").toString().toStdString().c_str());
        unsigned int ms = frame.value("ms").toInt(0);

        a->AddFrame(image, Frame::DrawMethod(drawMethod), ms);
    }
}

void SurfaceManager::MakeBalloonSurface(QJsonObject &obj) {

    unsigned int id = obj.value("id").toInt();
    QString image = imagePath + obj.value("image").toString();
    auto textarea = obj.value("textarea").toArray();

    balloonSurfaces.insert(id, new BalloonSurface(id, image, textarea.at(0).toInt(), textarea.at(1).toInt(),
                                                  textarea.at(2).toInt(), textarea.at(3).toInt()));

}

unsigned int SurfaceManager::GetLayerCount() const
{
    return layerCount;
}

QVector<Surface *> SurfaceManager::GetDefaultSurfaces() const
{
    QVector<Surface*> vector;
    vector.append(surfaces.value(0));
    vector.append(surfaces.value(100));
    return vector;
}

QVector<BalloonSurface *> SurfaceManager::GetDefaultBalloons() const
{
    QVector<BalloonSurface*> vector;
    vector.append(balloonSurfaces.value(0));
    return vector;
}
