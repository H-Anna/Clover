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
    path = R"(..\..\data)";
#elif unix || __unix || __unix__
    path = R"(../data)";
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
            sm->LoadSurfaces(&json, DATAPATH);
        }
    }

    MainProcess* mainproc = new MainProcess();

    auto tc = tm->MakeTokens(tm->GetTalk(1000));
    mainproc->SaveTokenCollection(tc);
    mainproc->EvaluateTokens();

    return a.exec();
}
