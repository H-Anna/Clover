#include <ghostwidget.h>
#include <balloonwidget.h>
#include <surface.h>

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>


#define IMAGEPATH R"(Z:\GhostTest/data)"

QFile* summaryFile;
QFile* talksFile;
QList<Surface> surfaceList;
QStringList talksList;

bool loadSurfaces()
{
    //Read summary.json and load contents into surfaceList
    summaryFile->open(QIODevice::ReadOnly);
    QString summary = summaryFile->readAll();
    summaryFile->close();

    QJsonObject jsonDoc = QJsonDocument::fromJson(summary.toUtf8()).object();
    QJsonArray surfaceArray = jsonDoc.value("surfaces").toArray();

    surfaceList = QList<Surface>();
    for (int i = 0; i < surfaceArray.count(); i++) {
        unsigned int id = surfaceArray.at(i)["id"].toInt();
        QString img = QString(IMAGEPATH) + "\\" + surfaceArray.at(i)["image"].toString();

        QString alias;
        if (surfaceArray.at(i)["alias"] != QJsonValue::Null)
            alias = surfaceArray.at(i)["alias"].toString();

        surfaceList.append(Surface(id, img, alias));
    }

    std::cout << "Surfaces loaded: " << surfaceList.count() << std::endl;
    std::cout << "ID\tImage\tAlias" << std::endl;
    for (auto &it: surfaceList) {
        std::cout << it.id << "\t" << it.image.toStdString() << "\t" << it.alias.toStdString() << std::endl;
    }
    return true;
}

bool loadTalks()
{
    //Read talks.json and load contents into talksList
    talksFile->open(QIODevice::ReadOnly);
    QString talks = talksFile->readAll();
    talksFile->close();

    QJsonObject jsonDoc = QJsonDocument::fromJson(talks.toUtf8()).object();
    QJsonArray talksArray = jsonDoc.value("talks").toArray();

    talksList = QStringList();
    for (int i = 0; i < talksArray.count(); i++) {
        talksList.append(talksArray.at(i).toString());
    }

    std::cout << "Talks loaded: " << talksList.count() << std::endl;
    for (auto &it: talksList) {
        std::cout << it.toStdString() << std::endl;
    }
    return true;
}

bool loadDir(QString absolutePath)
{
    QDir imgDir = QDir(absolutePath);
    auto filesInfoList = imgDir.entryInfoList(QDir::Files);

    if (filesInfoList.empty()) {
        std::cout << "No files in directory!" << std::endl;
        return false;
    }

    for (auto &it: filesInfoList) {
        if (it.fileName() == "summary.json") {
            summaryFile = new QFile(it.absoluteFilePath());
        } else if (it.fileName() == "talks.json") {
            talksFile = new QFile(it.absoluteFilePath());
        }
    }

    if (summaryFile == nullptr) {
        std::cout << "No summary file found!" << std::endl;
        return false;
    }
    if (talksFile == nullptr) {
        std::cout << "No talks file found!" << std::endl;
        return false;
    }

    loadSurfaces();
    loadTalks();

//    nextImage();
//    if (filesInfoList.count() > 0) {
//        fileIdx = 0;
//        currentFileInfo = filesInfoList[fileIdx];
//    }
    return true;
}

int main(int argc, char *argv[])
{
    loadDir(IMAGEPATH);
    QApplication a(argc, argv);
    GhostWidget* w = new GhostWidget();
    BalloonWidget* b = new BalloonWidget();
    w->show();
    b->show();
    return a.exec();
}
