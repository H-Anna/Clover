#include <mainprocess.h>
#include <filereader.h>
#include <talkmanager.h>
#include <surfacemanager.h>
#include <talkparser.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ///Load files with FileReader as JSON objects

    QList<QJsonObject> jsonObjects;

    if (!FileReader::ReadFiles(&jsonObjects)) {
        std::cout << "ERROR - FileReader: Something happened during file reading." << std::endl;
    }

    ///Make Manager classes parse the loaded files

    TalkManager* tm = new TalkManager();
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

    auto tokens = TalkParser::Parse(tm->GetTalk(1000));

    MainProcess* mainproc = new MainProcess();

    return a.exec();
}
