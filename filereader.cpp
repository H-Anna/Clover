#include "filereader.h"

bool FileReader::ReadFiles(QList<QJsonObject> *validObjects, const QString &absolutePath)
{
    int validCount = 0;

    auto filesInfoList = QDir(absolutePath).entryInfoList(QDir::Files);

    if (filesInfoList.empty()) {
        std::cout << "ERROR - FileReader - No files in directory!" << std::endl;
        return false;
    }

    ///Read files, convert to JSON object and determine if it can be parsed

    for (auto &it: filesInfoList) {

        auto file = new QFile(it.absoluteFilePath());
        file->open(QIODevice::ReadOnly);
        QString contents = file->readAll();
        file->close();

        QJsonObject json = QJsonDocument::fromJson(contents.toUtf8()).object();

        if (json.empty())
            continue;

        QString type = json.value("type").toString();

        if (type.isEmpty())
            continue;

        validObjects->append(json);
        validCount++;
    }

    std::cout << "INFO - FileReader - Read " << validCount << " files as valid JSONs." << std::endl;

    return true;
}
