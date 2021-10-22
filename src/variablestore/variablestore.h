#ifndef VARIABLESTORE_H
#define VARIABLESTORE_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QSettings>
#include <QFile>

class VariableStore
{
    typedef QString (*globalFuncPtr)();

public:
    VariableStore(const QString &_iniFile);
    ~VariableStore();
    QVariant GetVariable(const QString& key);
    void SetVariable(const QString& key, const QVariant& value);

private:
    QString iniFile;
    QMap<QString, QVariant> variables;
    QMap<QString, globalFuncPtr> globalFunctions;

    void BuildLambdaMap();
    void LoadIni();
    void UnloadIni();
};

#endif // VARIABLESTORE_H
