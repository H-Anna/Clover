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

QVariant VariableStore::GetVariable(const QString &key)
{
    if (globalFunctions.contains(key)) {
        return globalFunctions.value(key);
    }

    return variables.value(key, QString(""));
}

void VariableStore::SetVariable(const QString &key, const QVariant &value)
{
    variables[key] = value;
}

void VariableStore::BuildLambdaMap()
{
    globalFunctions = QMap<QString, globalFuncPtr>();

    // TODO: why do these return true????

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
