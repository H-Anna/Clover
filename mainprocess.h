#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <ghostwidget.h>
#include <balloonwidget.h>
#include <talkmanager.h>

#include <QRegularExpression>

class MainProcess: public QObject
{
    Q_OBJECT
public:
    MainProcess(TalkManager& tm);
    ~MainProcess();

public slots:
    void EvaluateToken(const QString& token);
    void Test();

signals:

private:
    void BuildTagLambdaMap();

    QList<GhostWidget*> ghostWidgets;
    QList<BalloonWidget*> balloonWidgets;

    QString currentToken;
    //QMap<QString, void(*)(const QStringList &)> tagLambdaMap;
    QRegularExpression tagRegex;

    GhostWidget* ghostInScope;
    BalloonWidget* balloonInScope;

signals:
    void testSignal();
    bool changeSurfaceSignal(int id);
    bool changeSurfaceSignal(const QString& alias);
    bool balloonClearSignal();

//    void tokenEvaluatedSignal();

};

#endif // MAINPROCESS_H
