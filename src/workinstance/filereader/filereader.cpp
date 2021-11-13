#include "filereader.h"

bool FileReader::ReadFiles(QList<QJsonObject> *validObjects, QString *iniFile, QString *stylesheet, const QString &absolutePath)
{
    int validCount = 0;

    auto filesInfoList = QDir(absolutePath).entryInfoList(QDir::Files);

    if (filesInfoList.isEmpty()) {
        qDebug() << "ERROR - FileReader - No files in directory!";
        return false;
    }

    ///Read files, convert to JSON object and determine if it can be parsed

    for (auto &it: filesInfoList) {

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

        if (it.fileName().endsWith(".json")) {

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
            validCount++;
        }
    }

    qDebug().noquote() << QString("INFO - FileReader - Read %1 files as valid JSONs.").arg(validCount);

    return true;
}
