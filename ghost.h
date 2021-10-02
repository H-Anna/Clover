#ifndef GHOST_H
#define GHOST_H

#include <ghostwidget.h>
#include <QObject>

class Ghost: public QObject
{
    Q_OBJECT;
public:
    Ghost();
    ~Ghost();
    void Hide();
    void Show();
    void ChangeSurface(const QString& path);

    GhostWidget *GetInScope() const;

private:
    QMap<int, GhostWidget*> ghosts;
    GhostWidget* inScope;
};

#endif // GHOST_H
