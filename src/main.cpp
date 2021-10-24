#include <mainprocess.h>
#include <filereader.h>
#include <talkmanager.h>
#include <surfacemanager.h>
//#include <inputreceiver.h>
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

    /// Make Manager classes parse the loaded files

    TalkManager* tm = new TalkManager(R"(<! ?(\w+(?:-\w+)*)(?: ?\[(\w+(?:-\w+)*(?:, ?-?\w+(?:-\w+)*)*)\])* ?>)",
                                      R"(<[^!].*?>)");
    SurfaceManager* sm = new SurfaceManager();
    SoundEmitter* se = new SoundEmitter();

    QString aPath = dataDir.absolutePath() + QDir::separator();

    for (auto &json: jsonObjects) {
        QString type = json.value("type").toString();

        if (type == "talk") {
            tm->LoadTalks(&json);
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

    /// Load variables from ini file(s)
    auto vs = VariableStore(iniFile);

    MainProcess* mainproc = new MainProcess(&vs, sm->GetLayerCount(), sm->GetDefaultSurfaces(), sm->GetDefaultBalloons());

    QObject::connect(mainproc, SIGNAL(applySurfaceSignal(QStringList)),
            sm, SLOT(ApplySurface(QStringList)));

    QObject::connect(mainproc, SIGNAL(applyBalloonSignal(QStringList)),
            sm, SLOT(ApplyBalloon(QStringList)));

    QObject::connect(mainproc, SIGNAL(applyAnimationSignal(QStringList,Surface*)),
            sm, SLOT(ApplyAnimation(QStringList,Surface*)));

    QObject::connect(sm, SIGNAL(animateGhostSignal(Animation*,Frame*)),
                     mainproc->GetGhost(), SLOT(AnimateGhost(Animation*,Frame*)));

    QObject::connect(sm, SIGNAL(changeSurfaceSignal(Surface*)),
                     mainproc->GetGhost(), SLOT(ChangeSurface(Surface*)));

    QObject::connect(sm, SIGNAL(changeBalloonSignal(BalloonSurface*)),
                     mainproc->GetBalloon(), SLOT(ChangeBalloon(BalloonSurface*)));

    QObject::connect(mainproc, SIGNAL(playSoundSignal(const QString&, int)),
                     se, SLOT(Play(const QString&, int)));

    QObject::connect(mainproc, SIGNAL(stopSoundSignal()),
                     se, SLOT(Stop()));

    //TODO random talk
    auto tc = tm->MakeTokens(tm->GetTalk(1000));
    mainproc->SaveTokenCollection(tc);
    mainproc->EvaluateTokens();

    //InputReceiver ir;

    return a.exec();
}
