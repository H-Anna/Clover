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

    if (surfaceArray.empty())
        return false;

    for (int i = 0; i < surfaceArray.count(); i++) {
        auto obj = surfaceArray.at(i).toObject();
        MakeSurface(obj);
    }

    return true;
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    if (surfaceIDMap.count() > 0) {
        qDebug() << "Surfaces loaded:" << surfaceIDMap.count();
        qDebug() << "ID\tImage\tAlias";

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

Surface* SurfaceManager::GetSurface(const QString &alias)
{
    if (surfaceAliasMap.keys().contains(alias))
        return surfaceAliasMap[alias];

    return nullptr;
}

void SurfaceManager::MakeSurface(QJsonObject &obj)
{
    /// Make surface

    unsigned int id = obj["id"].toInt();
    QString img = imagePath + obj["image"].toString();

    QString alias = obj["alias"].toString("");

    auto s = new Surface(id, img, alias);
    surfaceIDMap.insert(s->GetId(), s);
    if (s->HasAlias())
        surfaceAliasMap.insert(s->GetAlias(), s);

    /// Make animations

    QJsonArray animArray = obj["animations"].toArray();
    if (animArray.empty())
        return;

    for (int i = 0; i < animArray.count(); i++) {
        auto obj = animArray.at(i).toObject();
        MakeAnimation(obj, *s);
    }
}

void SurfaceManager::MakeAnimation(QJsonObject &obj, Surface& s)
{
    /// If there are no frames, ignore animations

    QJsonArray framesArray = obj["frames"].toArray();
    if (framesArray.empty())
        return;

    /// Make animation & frames

    unsigned int id = obj["id"].toInt();
    DrawMethod drawMethod = drawMethodMap.value(obj["drawmethod"].toString().toLower());
    auto a = s.AddAnimation(id, drawMethod);

    for (int k = 0; k < framesArray.count(); k++) {

        /// Make a frame

        QJsonObject frame = framesArray.at(k).toObject();

        unsigned int id = frame["id"].toInt();
        QString image = frame["image"].toString();
        DrawMethod drawMethod = drawMethodMap.value(frame["drawmethod"].toString().toLower());

        a->AddFrame(id, image, drawMethod);
    }
}
