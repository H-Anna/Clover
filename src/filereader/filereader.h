#ifndef FILEREADER_H
#define FILEREADER_H

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>

class FileReader
{
public:
    static bool ReadFiles(QList<QJsonObject>* validObjects, QString *iniFile, const QString& absolutePath);
};

#endif // FILEREADER_H
