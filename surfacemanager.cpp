#include "surfacemanager.h"

SurfaceManager::SurfaceManager()
{

}

SurfaceManager::~SurfaceManager()
{

}

bool SurfaceManager::LoadSurfaces(QJsonObject *json, const QString &imgPath)
{
    /// Read JSON object, load contents into surfaceList

#ifdef _WIN32
    imagePath = imgPath + "\\";
#elif unix || __unix || __unix__
    imagePath = imgPath + "\/";
#endif

    QJsonArray surfaceArray = json->value("surfaces").toArray();

    if (surfaceArray.isEmpty())
        return false;

    for (int i = 0; i < surfaceArray.count(); i++) {
        auto obj = surfaceArray.at(i).toObject();
        MakeSurface(obj);
    }

    return true;
}

void SurfaceManager::Animate(Animation* a, Ghost &g)
{
    auto f = g.ApplyAnimation(a);

    if (f == nullptr) {

        delete timers.value(a);
        timers.remove(a);

        return;
    }

    QTimer* timer;

    if (timers.keys().contains(a)) {
        timer = timers.value(a);
    } else {
        timer = new QTimer(this);
        timers[a] = timer;
        timer->callOnTimeout(this, [this, a, &g](){ Animate(a, g); });
        timer->setSingleShot(true);
    }

    timer->setInterval(f->GetMs());
    timer->start();
}

void SurfaceManager::ApplyGraphics(const QString &tag, QStringList params, Ghost &g)
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

        g.ChangeSurface(s);

    } else if (tag == "i") {

        Surface* s = g.GetCurrentSurface();

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

        Animate(a, g);
    }
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    if (surfaceIDMap.count() > 0) {
        qDebug() << "Surfaces loaded:" << surfaceIDMap.count();
        qDebug() << "ID\tImage\tName";

        for (auto &it: surfaceIDMap.keys()) {
            qDebug().noquote() << surfaceIDMap.value(it)->PrintData();
        }
    } else {
        qDebug() << "No surfaces loaded.";
    }
}

Surface *SurfaceManager::GetSurface(unsigned int id)
{
    if (surfaceIDMap.keys().contains(id))
        return surfaceIDMap[id];

    return nullptr;
}

Surface* SurfaceManager::GetSurface(const QString &name)
{
    if (surfaceNameMap.keys().contains(name))
        return surfaceNameMap[name];

    return nullptr;
}

void SurfaceManager::MakeSurface(QJsonObject &obj)
{
    /// Make surface

    unsigned int id = obj.value("id").toInt();
    QString img = imagePath + obj.value("image").toString();

    QString name = obj.value("name").toString("");

    auto s = new Surface(id, img, name);
    surfaceIDMap.insert(s->GetId(), s);
    if (s->HasName())
        surfaceNameMap.insert(s->GetName(), s);

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
    Frequency frequency = EnumConverter::GetFrequency(obj.value("frequency").toString().toLower());
    QString name = obj.value("name").toString("");
    auto a = s.AddAnimation(id, name, frequency);

    for (int k = 0; k < framesArray.count(); k++) {

        /// Make a frame

        QJsonObject frame = framesArray.at(k).toObject();
        QString image = imagePath + frame.value("image").toString();
        DrawMethod drawMethod = EnumConverter::GetDrawMethod(frame.value("drawmethod").toString().toLower());
        unsigned int ms = frame.value("ms").toInt();

        a->AddFrame(image, drawMethod, ms);
    }
}
