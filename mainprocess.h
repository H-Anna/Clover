#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <ghostwidget.h>
#include <balloonwidget.h>
#include <tokencollection.h>
#include <surfacemanager.h>

class MainProcess: public QObject
{
    typedef void (*tagLambdaPtr)(MainProcess&, const QStringList&);

    Q_OBJECT;
public:
    MainProcess(SurfaceManager *_sm);
    ~MainProcess();
    void SaveTokenCollection(TokenCollection &tc);

public slots:
    void EvaluateTokens();

signals:

private:
    void BuildTagLambdaMap();
    void ConnectTagSignals(const GhostWidget& w);
    void ConnectTagSignals(const BalloonWidget& w);
    void DisconnectTagSignals(const GhostWidget& w);
    void DisconnectTagSignals(const BalloonWidget& w);
    void ExecuteCommand(const Token& token);

    void PrintUndefinedTag(const QString& tag, const QStringList& params);

    QList<GhostWidget*> ghostWidgets;
    QList<BalloonWidget*> balloonWidgets;

    GhostWidget* ghostInScope;
    BalloonWidget* balloonInScope;

    QMap<QString, tagLambdaPtr> tagLambdaMap;

    TokenCollection* currentTC;
    int tokenCursor;

    SurfaceManager* sm;

signals:
    bool changeSurfaceSignal(int id);
    bool changeSurfaceSignal(const QString& alias);
    bool printTextSignal(const QString& text);

    void finishedTokenEvaluationSignal();

};

#endif // MAINPROCESS_H
