#include <mainprocess.h>
#include <filereader.h>
#include <talkmanager.h>
#include <surfacemanager.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// Load files with FileReader as JSON objects

    QList<QJsonObject> jsonObjects;

    if (!FileReader::ReadFiles(&jsonObjects)) {
       qDebug() << "ERROR - FileReader: Something happened during file reading.";
    }

    /// Make Manager classes parse the loaded files

    TalkManager* tm = new TalkManager(R"(<! ?(\w+(?:-\w+)*)(?: ?\[(\w+(?:-\w+)*(?:, ?-?\w+(?:-\w+)*)*)\])* ?>)");
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

    tm->PrintTalksList();
    sm->PrintSurfaceList();

    tm->Parse(tm->GetTalk(1000));
    qDebug() << tm->GetCurrentTokensList().count() << "token items received from TalkManager::Parse";

    MainProcess* mainproc = new MainProcess(*tm);

    tm->GetNextToken();

    return a.exec();
}
