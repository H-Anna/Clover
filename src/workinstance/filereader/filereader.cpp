#include "filereader.h"

bool FileReader::HasDataFolder(QString *folderPath)
{
    QDir dir(*folderPath);
    dir.setNameFilters(QStringList("data"));

    for (int i = 0; i < 4; i++)
    {
        auto list = dir.entryInfoList(QDir::Dirs, QDir::Name);

        if (list.length() >= 1) {
            *folderPath = QDir::cleanPath(list.at(0).absoluteFilePath());
            return true;
        }

        dir.cdUp();
    }

    return false;
}

bool FileReader::ReadFiles(QList<QJsonObject> *validObjects, QString *iniFile, QString *stylesheet, const QString &absolutePath)
{
    int valid = 0;
    int total = 0;
    QDir dir(absolutePath);
    QStringList JSON("*.json");
    QStringList OTHER({"variables.ini", "default.ini", "stylesheet.qss"});

    dir.setNameFilters(JSON);
    auto jsonList = dir.entryInfoList(QDir::Files);
    dir.setNameFilters(OTHER);
    auto otherList = dir.entryInfoList(QDir::Files);

    if (jsonList.isEmpty()) {
        qDebug() << "ERROR - FileReader - No JSON files in directory!";
        return false;
    }

    total = jsonList.count();

    ///Read files, convert to JSON object and determine if it can be parsed

    for(auto &it: jsonList)
    {
        auto file = new QFile(it.absoluteFilePath());
        file->open(QIODevice::ReadOnly);
        QString contents = file->readAll();
        file->close();

        QJsonObject json = QJsonDocument::fromJson(contents.toUtf8()).object();

        if (json.isEmpty()) {
            qDebug().noquote() << QString("WARNING - FileReader - File %1 has invalid JSON. "
                                          "Unable to process. Skipping file.").arg(file->fileName());
            continue;
        }

        QString type = json.value("type").toString();

        if (type.isEmpty()) {
            qDebug().noquote() << QString("WARNING - FileReader - File %1 has invalid JSON. "
                        "No 'type' defined. Skipping file.").arg(file->fileName());
            continue;
        }

        delete file;

        validObjects->append(json);
        valid++;
    }

    if (otherList.isEmpty()) {
        qDebug() << "ERROR - FileReader - No .ini or .qss files in directory!";
        return false;
    }
    for (auto &it: otherList) {

        if (it.fileName().endsWith(".ini")) {

            *iniFile = it.absoluteFilePath();
        }

        if (it.fileName().endsWith(".qss")) {

            auto file = new QFile(it.absoluteFilePath());
            file->open(QIODevice::ReadOnly);
            *stylesheet = file->readAll();
            file->close();
            delete file;

        }
    }

    qDebug().noquote() << QString("INFO - FileReader - Read %1 valid JSONs (out of %2 total.)").arg(valid).arg(total);

    return true;
}
