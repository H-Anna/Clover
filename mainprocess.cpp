#include "mainprocess.h"

MainProcess::MainProcess()
{
    ghostWidgets = QList<GhostWidget*>();
    balloonWidgets = QList<BalloonWidget*>();

    ghostWidgets.append(new GhostWidget());
    balloonWidgets.append(new BalloonWidget());

    ghostWidgets.at(0)->show();
    balloonWidgets.at(0)->show();
}
