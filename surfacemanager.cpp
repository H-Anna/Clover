#include "surfacemanager.h"

SurfaceManager::SurfaceManager()
{

}

SurfaceManager::~SurfaceManager()
{

}

bool SurfaceManager::LoadSurfaces(QJsonObject *json, const QString &imgPath)
{
    /// Read JSON object and load contents into surfaceList

    QJsonArray surfaceArray = json->value("surfaces").toArray();

    for (int i = 0; i < surfaceArray.count(); i++) {
        unsigned int id = surfaceArray.at(i)["id"].toInt();
        QString img = imgPath + "\\" + surfaceArray.at(i)["image"].toString();

        QString alias;
        if (surfaceArray.at(i)["alias"] != QJsonValue::Null)
            alias = surfaceArray.at(i)["alias"].toString();

        surfaceList.append(Surface(id, img, alias));
    }

    return true;
}

void SurfaceManager::PrintSurfaceList()
{
    qDebug() << "INFO - SurfaceManager";

    //std::cout << "INFO - SurfaceManager" << std::endl;

    if (surfaceList.count() > 0) {
        qDebug() << "Surfaces loaded:" << surfaceList.count();
        qDebug() << "ID\tImage\tAlias";

        for (auto &it: surfaceList) {
            qDebug().noquote() << it.PrintData();
        }
    } else {
        qDebug() << "No surfaces loaded.";
    }
}
