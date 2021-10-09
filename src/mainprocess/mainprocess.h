#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <ghost.h>
#include <balloon.h>
#include <tokencollection.h>

class MainProcess: public QObject
{
    typedef void (*tagLambdaPtr)(MainProcess&, const QStringList&);

    Q_OBJECT;
public:
    MainProcess(unsigned int _layerCount);
    ~MainProcess();
    void SaveTokenCollection(TokenCollection &tc);

    Ghost* GetGhost() const;
    Balloon* GetBalloon() const;

signals:
    void applyGraphicsSignal(const QString& tag, QStringList params, Surface* currentSurface);
public slots:
    void EvaluateTokens();

private:
    void BuildTagLambdaMap();
    void ExecuteCommand(const Token& token);
    void PrintUndefinedTag(const QString& tag, const QStringList& params);

    Ghost* ghost;
    Balloon* balloon;

    QMap<QString, tagLambdaPtr> tagLambdaMap;
    QMap<unsigned int,QList<unsigned int>> ghostBalloonsMap;

    TokenCollection* currentTC;
    unsigned int tokenCursor;

signals:
    bool printTextSignal(const QString& text);
    void finishedTokenEvaluationSignal();

};

#endif // MAINPROCESS_H
