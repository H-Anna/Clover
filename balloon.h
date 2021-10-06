#ifndef BALLOON_H
#define BALLOON_H

#include <balloonwidget.h>
#include <QObject>

class Balloon: public QObject
{
    Q_OBJECT;
public:
    Balloon();
    ~Balloon();

    void AppendHtml(const QString& text);
    void PrintBalloonContents();
    void ClearBalloon();

    BalloonWidget *GetInScope() const;
    unsigned int GetID(BalloonWidget* w) const;

signals:
    void printTextSignal(const QString& text);
    void finishedTextPrintSignal();

private:
    QMap<unsigned int, BalloonWidget*> balloons;
    BalloonWidget* inScope;
};

#endif // BALLOON_H
