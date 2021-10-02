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

    QJsonArray surfaceArray = json->value("surfaces").toArray();

    for (int i = 0; i < surfaceArray.count(); i++) {
        unsigned int id = surfaceArray.at(i)["id"].toInt();
        QString img = imgPath + "\\" + surfaceArray.at(i)["image"].toString();

        QString alias;
        if (surfaceArray.at(i)["alias"] != QJsonValue::Null)
            alias = surfaceArray.at(i)["alias"].toString();


        auto s = new Surface(id, img, alias);
        surfaceList.append(s);
        surfaceIDMap.insert(s->GetId(), s);
        if (s->HasAlias())
            surfaceAliasMap.insert(s->GetAlias(), s);

    }

    return true;
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    if (surfaceList.count() > 0) {
        qDebug() << "Surfaces loaded:" << surfaceList.count();
        qDebug() << "ID\tImage\tAlias";

        for (auto &it: surfaceList) {
            qDebug().noquote() << it->PrintData();
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
