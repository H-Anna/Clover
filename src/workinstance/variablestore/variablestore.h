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
    QVariant GetVariable(const QString& key) const;
    void SetVariable(const QString& key, const QVariant& value);

    QObject* GetMember(const QString& key) const;
    void AddMember(const QString& key, QObject* member);

    void ObserveVariable(const QString& key);

public slots:
    void increment(QString key);

private:
    QString iniFile;
    QMap<QString, QVariant> variables;
    QMap<QString, globalFuncPtr> globalFunctions;

    QMap<QString, QObject*> members;

    void BuildLambdaMap();
    void LoadIni();
    void UnloadIni();

signals:
    void anchorTalkSignal(QString scheme, QString anchor);

    //QObject* GetOwnMember(const QString& key);
};

#endif // VARIABLESTORE_H
