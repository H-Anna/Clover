#ifndef WORKINSTANCE_H
#define WORKINSTANCE_H

#include <filereader.h>
#include <mainprocess.h>
#include <talkmanager.h>
#include <surfacemanager.h>
#include <soundemitter.h>

class WorkInstance
{
public:
    WorkInstance(QString appDirPath);
    ~WorkInstance();

private:
    void ConnectThings();
    void SetupActions();

    MainProcess* mainProc;
    VariableStore* varStore;
    TalkManager* talkMan;
    SurfaceManager* surfaceMan;
    SoundEmitter* soundEmit;

    //QList<QMetaObject::Connection> connections;
};

#endif // WORKINSTANCE_H
