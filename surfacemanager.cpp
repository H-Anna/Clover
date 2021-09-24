#include "surfacemanager.h"

SurfaceManager::SurfaceManager()
{

}

SurfaceManager::~SurfaceManager()
{

}

bool SurfaceManager::LoadSurfaces(QJsonObject *json, const QString &imgPath)
{
    ///Read json object and load contents into surfaceList

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
    std::cout << "INFO - SurfaceManager" << std::endl;

    if (surfaceList.count() > 0) {
        std::cout << "Surfaces loaded: " << surfaceList.count() << std::endl;
        std::cout << "ID\tImage\tAlias" << std::endl;

        for (auto &it: surfaceList) {
            std::cout << it.PrintData().toStdString() << std::endl;
        }
    } else {
        std::cout << "No surfaces loaded." << std::endl;
    }
}
