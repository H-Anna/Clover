#ifndef BALLOON_H
#define BALLOON_H

#include <balloonwidget.h>
#include <balloonsurface.h>

#include <QObject>

class Balloon: public QObject
{
    Q_OBJECT
public:
    Balloon(QVector<BalloonSurface*> _defaultBalloons);
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
};

#endif // BALLOON_H
