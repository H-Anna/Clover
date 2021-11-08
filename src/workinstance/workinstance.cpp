#include "workinstance.h"

WorkInstance::WorkInstance(QString appDirPath)
{
    QDir dataDir(appDirPath);
    QString path = QDir::cleanPath(
                QString("..") + QDir::separator() + ".." + QDir::separator() + ".." + QDir::separator() + "data");

    dataDir.setPath(path);

    /// Load files with FileReader as JSON objects

    QList<QJsonObject> jsonObjects;
    QString iniFile;

    if (!FileReader::ReadFiles(&jsonObjects, &iniFile, dataDir.absolutePath())) {
       qDebug() << "ERROR - FileReader: Something happened during file reading.";
    }

    /// Load variables from ini file(s)
    varStore = new VariableStore(iniFile);

    /// Make Manager classes parse the loaded files

    talkMan = new TalkManager(R"(<! ?(\w+(?:-\w+)*)(?: ?\[(\w+(?:-\w+)*(?:, ?-?\w+(?:-\w+)*)*)\])* ?>)",
                                      R"(<[^!].*?>)");
    surfaceMan = new SurfaceManager();
    soundEmit = new SoundEmitter();

    varStore->AddMember("VariableStore", varStore);
    varStore->AddMember("TalkManager", talkMan);
    varStore->AddMember("SurfaceManager", surfaceMan);
    varStore->AddMember("SoundEmitter", soundEmit);

    QString aPath = dataDir.absolutePath() + QDir::separator();

    for (auto &json: jsonObjects) {
        QString type = json.value("type").toString();

        if (type == "talk") {
            talkMan->LoadTalks(&json);
        }
        else if (type == "anchor") {
            talkMan->LoadAnchors(&json);
        }
        else if (type == "surface") {
            surfaceMan->LoadSurfaces(&json, aPath);
        }
        else if (type == "balloon") {
            surfaceMan->LoadBalloons(&json, aPath);
        }
        else if (type == "sound") {
            soundEmit->LoadSounds(&json, aPath);
        }
    }

    mainProc = new MainProcess(varStore, surfaceMan->GetLayerCount(), surfaceMan->GetDefaultSurfaces(), surfaceMan->GetDefaultBalloons());

    varStore->AddMember("MainProcess", mainProc);

    ConnectThings();

    talkMan->IndexedTalk(100);
}

WorkInstance::~WorkInstance()
{
    delete mainProc;
    delete varStore;
    delete talkMan;
    delete surfaceMan;
    delete soundEmit;
}

void WorkInstance::ConnectThings()
{
    QObject::connect(talkMan, &TalkManager::tokensReadySignal,
                     mainProc, &MainProcess::TokensReady);

    QObject::connect(mainProc, &MainProcess::applySurfaceSignal,
                     surfaceMan, &SurfaceManager::ApplySurface);

    QObject::connect(mainProc, &MainProcess::applyBalloonSignal,
                     surfaceMan, &SurfaceManager::ApplyBalloon);

    QObject::connect(mainProc, &MainProcess::applyAnimationSignal,
                     surfaceMan, &SurfaceManager::ApplyAnimation);

    QObject::connect(surfaceMan, &SurfaceManager::animateGhostSignal,
                     mainProc->GetGhost(), &Ghost::Animate);

    QObject::connect(surfaceMan, &SurfaceManager::changeSurfaceSignal,
                     mainProc->GetGhost(), &Ghost::ChangeSurface);

    QObject::connect(surfaceMan, &SurfaceManager::changeBalloonSignal,
                     mainProc->GetBalloon(), &Balloon::ChangeBalloon);

    QObject::connect(mainProc, &MainProcess::playSoundSignal,
                     soundEmit, &SoundEmitter::Play);

    QObject::connect(mainProc, &MainProcess::stopSoundSignal,
                     soundEmit, &SoundEmitter::Stop);
}