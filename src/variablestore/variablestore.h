#ifndef VARIABLESTORE_H
#define VARIABLESTORE_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QObject>

class VariableStore: public QObject
{
    Q_OBJECT

    typedef QString (*globalFuncPtr)();

public:
    VariableStore(const QString &_iniFile);
    ~VariableStore();
    QVariant GetVariable(const QString& key);
    void SetVariable(const QString& key, const QVariant& value);

    static QObject* GetMember(const QString& key);
    static void AddMember(const QString& key, QObject* member);

private:
    QString iniFile;
    QMap<QString, QVariant> variables;
    QMap<QString, globalFuncPtr> globalFunctions;

    static inline QMap<QString, QObject*> members;

    void BuildLambdaMap();
    void LoadIni();
    void UnloadIni();
};

#endif // VARIABLESTORE_H
