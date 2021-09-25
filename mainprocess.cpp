#include "mainprocess.h"

MainProcess::MainProcess(TalkManager &tm)
{
    ghostWidgets = QList<GhostWidget*>();
    balloonWidgets = QList<BalloonWidget*>();

    ghostInScope = new GhostWidget();
    ghostWidgets.append(ghostInScope);

    balloonInScope = new BalloonWidget();
    balloonWidgets.append(balloonInScope);

//    ghostWidgets.at(0)->show();
//    balloonWidgets.at(0)->show();

    connect(&tm, SIGNAL(TokenReadySignal(const QString&)), this, SLOT(EvaluateToken(const QString&)));
    connect(this, SIGNAL(testSignal()), this, SLOT(Test()));

    connect(this, SIGNAL(changeSurfaceSignal(int)), ghostInScope, SLOT(changeSurfaceSlot(int)));
    connect(this, SIGNAL(changeSurfaceSignal(const QString&)), ghostInScope, SLOT(changeSurfaceSlot(const QString&)));



    tagRegex = tm.GetTagRegex();
    BuildTagLambdaMap();
}

MainProcess::~MainProcess()
{
    while (!ghostWidgets.isEmpty()) {
        delete ghostWidgets.takeFirst();
    }

    while (!balloonWidgets.isEmpty()) {
        delete balloonWidgets.takeFirst();
    }

    delete ghostInScope;
    delete balloonInScope;
}

void MainProcess::EvaluateToken(const QString &token)
{
    QString tag;
    QStringList params = QStringList();

    auto match = tagRegex.match(token);

    ///Command tag
    if (match.hasMatch()) {
        ///Take tag (key in map) and see if there's any parameters

        tag = match.captured(1);
        auto _p = match.captured(2);

        if (!_p.isNull()) {
            auto _list = _p.split(',', Qt::SkipEmptyParts);

            for (auto &it: _list)
                it = it.trimmed();

            params = _list;
        }

        ///Choose lambda to execute based on tag, using a map
        ///TODO
    }
    ///Display text
    else {
        ///Emit "Print to balloon"
    }
}

void MainProcess::Test()
{
    qDebug() << "INFO - MainProcess - Test successful";
}

void MainProcess::BuildTagLambdaMap()
{
    /// This part fills me with existential dread
    /// With typedef we create a type for a function that takes in a MainProcess& and
    /// a const QStringList& as parameters and returns nothing. It is called "tagLambdaPtr".
    /// Then we assign this type as the value type for the QMap we build and then we can
    /// insert key-value pairs where the value is the function with the qualities described.
    /// I don't fully understand how it works, why it works and how I made it work.
    ///
    /// PLEASE DON'T CHANGE IT.

    typedef void (*tagLambdaPtr)(MainProcess&, const QStringList&);

    QMap<QString, tagLambdaPtr> tagLambdaMap;
    tagLambdaMap.insert("test", [](MainProcess& mp, const QStringList& params){ emit mp.testSignal(); });
    //tagLambdaMap.insert("clr", [](MainProcess& mp, const QStringList& params){ emit mp.balloonClearSignal(); });
    tagLambdaMap.insert("s",[](MainProcess& mp, const QStringList& params)
    {
        if (params.count() > 1) {
            qDebug() << "ERROR - MainProcess - Surface change tag has multiple parameters, UNHANDLED CASE. No signal emitted.";
            return;
        }

        QString str = params[0];
        bool canConvertToInt;
        str.toInt(&canConvertToInt);

        if (canConvertToInt) {

            //TODO: If multiple GhostWidgets are on screen, they will all receive this signal. Possible solutions:
            // - Pass ghostInScope as pointer in signal. Each GhostWidget that receives this signal must check if it is targeted at them.
            // - Call method of ghostInScope directly.
            // - Call a method of SurfaceManager that fetches the surface and tells the correct widget to change it.
                //Favorable. Store pointer via MP constructor?

            emit mp.changeSurfaceSignal(str.toInt());
        } else {
            emit mp.changeSurfaceSignal(str);
        }

    });

    tagLambdaMap["test"](*this, QStringList());
    tagLambdaMap["s"](*this, QStringList("2"));
    tagLambdaMap["s"](*this, QStringList("happy"));
}


