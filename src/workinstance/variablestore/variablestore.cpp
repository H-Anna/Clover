#include "variablestore.h"

VariableStore::VariableStore(const QString& _iniFile):
    iniFile(_iniFile)
{
    BuildLambdaMap();
    LoadIni();
}

VariableStore::~VariableStore()
{
    UnloadIni();
}

QVariant VariableStore::GetVariable(const QString &key) const
{
    if (globalFunctions.contains(key)) {
        return globalFunctions.value(key)();
    }

    return variables.value(key, QString(""));
}

void VariableStore::SetVariable(const QString &key, const QVariant &value)
{
    /// If the key exists, replace its value; otherwise append the key-value pair to the map
    variables[key] = value;
}

QObject *VariableStore::GetMember(const QString &key) const
{
    if (!members.contains(key)) {
        qDebug() << QString("ERROR - VariableStore - Member with key %1 doesn't exist, nullptr returned.").arg(key);
    }

    return members.value(key, nullptr);
}

void VariableStore::AddMember(const QString &key, QObject *member)
{
    if (members.contains(key)) {
        qDebug() << QString("WARNING - VariableStore - Member with key %1 already exists.").arg(key);
    } else {
        members[key] = member;
    }
}

void VariableStore::ObserveVariable(const QString &key)
{
    if (!variables.contains(key)) {
        return;
    }

    /// TODO: delet this

    bool ok;
    int v = variables.value(key).toInt(&ok);
    if (ok && v == 100) {
        variables[key] = QVariant(v % 100);
        emit anchorTalkSignal("anchor", key);
    }
}

void VariableStore::increment(QString key)
{
    if (!variables.contains(key)) {
        return;
    }

    bool ok;
    int v = variables.value(key).toInt(&ok);
    if (ok) {
        v++;
        variables[key] = v;
    }

    ObserveVariable(key);
}

void VariableStore::BuildLambdaMap()
{
    globalFunctions = QMap<QString, globalFuncPtr>();

    globalFunctions.insert("TIME", [](){

        return QDateTime::currentDateTime().toString();
    });

    globalFunctions.insert("INT", [](){

        return QString::number(12345);
    });
}

void VariableStore::LoadIni()
{
    variables.clear();

    QSettings s(iniFile, QSettings::IniFormat);

    s.beginGroup("Clover");
    for (auto &key: s.childKeys()) {

        /// If an empty string is read, skip. Please don't set your variables to empty strings.
        if (s.value(key) != "")
            variables[key] = s.value(key);
    }
    s.endGroup();
}

void VariableStore::UnloadIni()
{
    QSettings s(iniFile, QSettings::IniFormat);

    s.clear();
    s.beginGroup("Clover");
    auto _keys = variables.keys();
    for (auto &key: _keys) {
        s.setValue(key, variables.value(key));
    }
    s.endGroup();
}
