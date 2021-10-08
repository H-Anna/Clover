#ifndef FILEREADER_H
#define FILEREADER_H

#define DATAPATH R"(D:\D_Programs\GitHub\GhostTest\data)"

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>

class FileReader
{
public:
    static bool ReadFiles(QList<QJsonObject>* validObjects, const QString& absolutePath = DATAPATH);
};

#endif // FILEREADER_H
