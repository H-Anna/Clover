#ifndef FILEREADER_H
#define FILEREADER_H

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class FileReader
{
public:
    static bool HasDataFolder(QString* folder);
    static bool ReadFiles(QList<QJsonObject>* validObjects, QString *iniFile, QString *stylesheet, const QString& absolutePath);
    //static QString GetContents(const QString& file);
};

#endif // FILEREADER_H
