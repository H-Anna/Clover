#include <mainprocess.h>
#include <filereader.h>
#include <talkmanager.h>
#include <surfacemanager.h>
#include <soundemitter.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dataDir(a.applicationDirPath());
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
    auto vs = new VariableStore(iniFile);

    /// Make Manager classes parse the loaded files

    TalkManager* tm = new TalkManager(R"(<! ?(\w+(?:-\w+)*)(?: ?\[(\w+(?:-\w+)*(?:, ?-?\w+(?:-\w+)*)*)\])* ?>)",
                                      R"(<[^!].*?>)");
    SurfaceManager* sm = new SurfaceManager();
    SoundEmitter* se = new SoundEmitter();

    VariableStore::AddMember("VariableStore", vs);
    VariableStore::AddMember("TalkManager", tm);
    VariableStore::AddMember("SurfaceManager", sm);
    VariableStore::AddMember("SoundEmitter", se);

    QString aPath = dataDir.absolutePath() + QDir::separator();

    for (auto &json: jsonObjects) {
        QString type = json.value("type").toString();

        if (type == "talk") {
            tm->LoadTalks(&json);
        }
        else if (type == "anchor") {
            tm->LoadAnchors(&json);
        }
        else if (type == "surface") {
            sm->LoadSurfaces(&json, aPath);
        }
        else if (type == "balloon") {
            sm->LoadBalloons(&json, aPath);
        }
        else if (type == "sound") {
            se->LoadSounds(&json, aPath);
        }
    }

    MainProcess* mainproc = new MainProcess(vs, sm->GetLayerCount(), sm->GetDefaultSurfaces(), sm->GetDefaultBalloons());

    VariableStore::AddMember("MainProcess", mainproc);

    QObject::connect(tm, &TalkManager::tokensReadySignal,
                     mainproc, &MainProcess::TokensReady);

    QObject::connect(mainproc, &MainProcess::applySurfaceSignal,
                     sm, &SurfaceManager::ApplySurface);

    QObject::connect(mainproc, &MainProcess::applyBalloonSignal,
                     sm, &SurfaceManager::ApplyBalloon);

    QObject::connect(mainproc, &MainProcess::applyAnimationSignal,
                     sm, &SurfaceManager::ApplyAnimation);

    QObject::connect(sm, &SurfaceManager::animateGhostSignal,
                     mainproc->GetGhost(), &Ghost::Animate);

    QObject::connect(sm, &SurfaceManager::changeSurfaceSignal,
                     mainproc->GetGhost(), &Ghost::ChangeSurface);

    QObject::connect(sm, &SurfaceManager::changeBalloonSignal,
                     mainproc->GetBalloon(), &Balloon::ChangeBalloon);

    QObject::connect(mainproc, &MainProcess::playSoundSignal,
                     se, &SoundEmitter::Play);

    QObject::connect(mainproc, &MainProcess::stopSoundSignal,
                     se, &SoundEmitter::Stop);

    tm->IndexedTalk(100);

    return a.exec();
}
