#include "surfacemanager.h"

SurfaceManager::SurfaceManager()
{

}

SurfaceManager::~SurfaceManager()
{
    for (auto &it: surfaces) {
        delete it;
    }
    for (auto &it: timers.values()) {
        delete it;
    }
}

bool SurfaceManager::LoadBalloons(QJsonObject *json, const QString &imgPath)
{
    /// Read JSON object, load contents into surfaceList

#ifdef _WIN32
    imagePath = imgPath + "\\";
#elif unix || __unix || __unix__
    imagePath = imgPath + "\/";
#endif

    QJsonArray balloonArray = json->value("balloons").toArray();

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

    emit changeSurfaceSignal(surfaces.value(0));
    emit changeBalloonSignal(balloonSurfaces.value(0));
}

bool SurfaceManager::LoadSurfaces(QJsonObject *json, const QString &imgPath)
{
    /// Read JSON object, load contents into surfaceList

#ifdef _WIN32
    imagePath = imgPath + "\\";
#elif unix || __unix || __unix__
    imagePath = imgPath + "\/";
#endif

    layerCount = json->value("layercount").toInt();
    QJsonArray surfaceArray = json->value("surfaces").toArray();

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

    emit applyAnimationSignal(a, f);

    if (f->GetMs() == 0)
        return;

    QTimer* timer;

    if (timers.keys().contains(a)) {
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

void SurfaceManager::ApplyGraphics(const QString &tag, QStringList params, Surface *currentSurface)
{
    QString str = params[0];
    bool canConvertToInt;
    str.toInt(&canConvertToInt);

    if (tag == "s") {

        Surface* s;
        if (canConvertToInt) {
            s = GetSurface(str.toInt());
        } else {
            s = GetSurface(str);
        }

        if (s == nullptr) {
            qDebug().nospace() << "WARNING - SurfaceManager - No surface found with param " << str << ", skipping to next token.";
            return;
        }

        /// Apply surface

        //g.ChangeSurface(s);
        emit changeSurfaceSignal(s);

        /// If it has animations that always play, play them.

        auto always = s->GetAlwaysAnimations();

        if (always.length() > 0) {
            for (auto &it: always) {
                Animate(it);
            }
        }

    } else if (tag == "i") {

        Surface* s = currentSurface;

        Animation* a = nullptr;
        if (canConvertToInt) {
            a = s->GetAnimation(str.toInt());
        } else {
            a = s->GetAnimation(str);

        }

        if (a == nullptr) {
            qDebug().nospace() << "WARNING - SurfaceManager - No animation found with param " << str << ", skipping to next token.";
            return;
        }

        Animate(a);
    }
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    if (surfaces.count() > 0) {
        qDebug() << "Surfaces loaded:" << surfaces.count();
        qDebug() << "ID\tImage\tName";

        for (auto &it: surfaces.keys()) {
            qDebug().noquote() << surfaces.value(it)->PrintData();
        }
    } else {
        qDebug() << "No surfaces loaded.";
    }
}

Surface *SurfaceManager::GetSurface(unsigned int id)
{
    if (surfaces.keys().contains(id))
        return surfaces[id];

    return nullptr;
}

Surface* SurfaceManager::GetSurface(const QString &name)
{
    if (namedSurfaces.keys().contains(name))
        return namedSurfaces[name];

    return nullptr;
}

void SurfaceManager::MakeSurface(QJsonObject &obj)
{
    /// Make surface

    unsigned int id = obj.value("id").toInt();
    auto elements = obj.value("elements").toArray();

    QString name = obj.value("name").toString("");

    auto s = new Surface(id, name);
    surfaces.insert(s->GetId(), s);
    if (s->HasName())
        namedSurfaces.insert(s->GetName(), s);

    for (auto it: elements) {
        s->AddElement(imagePath + it.toString());
    }

    /// Make animations

    QJsonArray animArray = obj.value("animations").toArray();
    if (animArray.isEmpty())
        return;

    for (int i = 0; i < animArray.count(); i++) {
        auto obj = animArray.at(i).toObject();
        MakeAnimation(obj, *s);
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
    Frequency frequency = EnumConverter::GetFrequency(obj.value("frequency").toString().toLower());
    QString name = obj.value("name").toString("");
    auto a = s.AddAnimation(id, name, frequency, layer);

    for (int k = 0; k < framesArray.count(); k++) {

        /// Make a frame

        QJsonObject frame = framesArray.at(k).toObject();
        QString image = imagePath + frame.value("image").toString();
        DrawMethod drawMethod = EnumConverter::GetDrawMethod(frame.value("drawmethod").toString().toLower());
        unsigned int ms = frame.value("ms").toInt(0);

        a->AddFrame(image, drawMethod, ms);
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
