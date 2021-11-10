#ifndef BALLOON_H
#define BALLOON_H

#include <balloonwidget.h>
#include <balloonsurface.h>

#include <QObject>

class Balloon: public QObject
{
    Q_OBJECT
public:
    Balloon(VariableStore* _varStore, QVector<BalloonSurface*> _defaultBalloons);
    ~Balloon();

    void AppendHtml(const QString& text);
    void PrintBalloonContents();
    void ClearBalloon();
    void ChangeTextSpeed(unsigned int newSpeed);
    void Reset();

    BalloonWidget *GetInScope() const;
    unsigned int GetID(BalloonWidget* w) const;


signals:
    void printTextSignal(QString text);
    void finishedTextPrintSignal();
    void timeoutSignal();
    void setTimeoutSignal(unsigned int time);

public slots:
    void ChangeBalloon(BalloonSurface* b);
    void ChangeScope(unsigned int id);

private:
    void ConnectScope();
    void DisconnectScope();

    QVector<BalloonWidget*> balloons;
    BalloonWidget* inScope;
    unsigned int idInScope;

    QVector<BalloonSurface*> defaultBalloons;
    VariableStore* varStore;
};

#endif // BALLOON_H
