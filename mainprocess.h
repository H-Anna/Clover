#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <ghostwidget.h>
#include <balloonwidget.h>

class MainProcess
{
public:
    MainProcess();

private:
    QList<GhostWidget*> ghostWidgets;
    QList<BalloonWidget*> balloonWidgets;
};

#endif // MAINPROCESS_H
