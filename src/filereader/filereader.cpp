#include "filereader.h"

bool FileReader::ReadFiles(QList<QJsonObject> *validObjects, const QString &absolutePath)
{
    int validCount = 0;

    auto filesInfoList = QDir(absolutePath).entryInfoList(QDir::Files);

    if (filesInfoList.isEmpty()) {
        qDebug() << "ERROR - FileReader - No files in directory!";
        return false;
    }

    ///Read files, convert to JSON object and determine if it can be parsed

    for (auto &it: filesInfoList) {

        if (!it.fileName().endsWith(".json"))
            continue;

        auto file = new QFile(it.absoluteFilePath());
        file->open(QIODevice::ReadOnly);
        QString contents = file->readAll();
        file->close();

        QJsonObject json = QJsonDocument::fromJson(contents.toUtf8()).object();

        if (json.isEmpty()) {
            qDebug() << "WARNING - FileReader - File" << file->fileName() << "has invalid JSON: "
                                                                             "unable to process, skipping to next file.";
            continue;
        }

        QString type = json.value("type").toString();

        if (type.isEmpty()) {
            qDebug() << "WARNING - FileReader - File" << file->fileName() << "has invalid JSON: "
                                                                             "no 'type' defined, skipping to next file.";
            continue;
        }

        validObjects->append(json);
        validCount++;
    }

    qDebug().nospace() << "INFO - FileReader - Read " << validCount << " files as valid JSONs.";

    return true;
}
