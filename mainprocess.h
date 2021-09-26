#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <ghostwidget.h>
#include <balloonwidget.h>
#include <talkmanager.h>

#include <QRegularExpression>


class MainProcess: public QObject
{
    typedef void (*tagLambdaPtr)(MainProcess&, const QStringList&);

    Q_OBJECT
public:
    MainProcess(TalkManager& tm);
    ~MainProcess();

public slots:
    void EvaluateToken(const QString& token);


signals:

private:
    void BuildTagLambdaMap();
    void ConnectTagSignals(const GhostWidget& w);
    void ConnectTagSignals(const BalloonWidget& w);
    void DisconnectTagSignals(const GhostWidget& w);
    void DisconnectTagSignals(const BalloonWidget& w);

    void printUndefinedTag(const QString& tag, const QStringList& params);

    QList<GhostWidget*> ghostWidgets;
    QList<BalloonWidget*> balloonWidgets;

    QString currentToken;
    QRegularExpression tagRegex;

    GhostWidget* ghostInScope;
    BalloonWidget* balloonInScope;

    QMap<QString, tagLambdaPtr> tagLambdaMap;



signals:
    bool changeSurfaceSignal(int id);
    bool changeSurfaceSignal(const QString& alias);
    bool printTextSignal(const QString& text);


    void finishedTokenEvaluationSignal();

};

#endif // MAINPROCESS_H
