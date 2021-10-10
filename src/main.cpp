#include <mainprocess.h>
#include <filereader.h>
#include <talkmanager.h>
#include <surfacemanager.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dataDir(a.applicationDirPath());
    QString path;

#ifdef _WIN32
    path = R"(..\..\..\data)";
#elif unix || __unix || __unix__
    path = R"(../../../data)";
#endif

    dataDir.cd(path);

    /// Load files with FileReader as JSON objects

    QList<QJsonObject> jsonObjects;

    if (!FileReader::ReadFiles(&jsonObjects, dataDir.absolutePath())) {
       qDebug() << "ERROR - FileReader: Something happened during file reading.";
    }

    /// Make Manager classes parse the loaded files

    TalkManager* tm = new TalkManager(R"(<! ?(\w+(?:-\w+)*)(?: ?\[(\w+(?:-\w+)*(?:, ?-?\w+(?:-\w+)*)*)\])* ?>)",
                                      R"(<[^!].*?>)");
    SurfaceManager* sm = new SurfaceManager();

    for (auto &json: jsonObjects) {
        QString type = json.value("type").toString();

        if (type == "talk") {
            tm->LoadTalks(&json);
        }
        else if (type == "surface") {
            sm->LoadSurfaces(&json, dataDir.absolutePath());
        }
        else if (type == "balloon") {
            sm->LoadBalloons(&json, dataDir.absolutePath());
        }
    }

    MainProcess* mainproc = new MainProcess(sm->GetLayerCount(), sm->GetDefaultSurfaces(), sm->GetDefaultBalloons());


    QObject::connect(mainproc, SIGNAL(applySurfaceSignal(QStringList)),
            sm, SLOT(ApplySurface(QStringList)));

    QObject::connect(mainproc, SIGNAL(applyBalloonSignal(QStringList)),
            sm, SLOT(ApplyBalloon(QStringList)));

    QObject::connect(mainproc, SIGNAL(applyAnimationSignal(QStringList, Surface*)),
            sm, SLOT(ApplyAnimation(QStringList, Surface*)));

    QObject::connect(sm, SIGNAL(animateGhostSignal(Animation*, Frame*)),
                     mainproc->GetGhost(), SLOT(AnimateGhost(Animation*, Frame*)));

    QObject::connect(sm, SIGNAL(changeSurfaceSignal(Surface*)),
                     mainproc->GetGhost(), SLOT(ChangeSurface(Surface*)));

    QObject::connect(sm, SIGNAL(changeBalloonSignal(BalloonSurface*)),
                     mainproc->GetBalloon(), SLOT(ChangeBalloon(BalloonSurface*)));


    //TODO random talk
    auto tc = tm->MakeTokens(tm->GetTalk(1000));
    mainproc->SaveTokenCollection(tc);
    mainproc->EvaluateTokens();

    return a.exec();
}
