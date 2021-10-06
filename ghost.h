#ifndef GHOST_H
#define GHOST_H

#include <ghostwidget.h>
#include <surface.h>

#include <QObject>

class Ghost: public QObject
{
    Q_OBJECT;
public:
    Ghost();
    ~Ghost();

    void Hide();
    void Show();
    void ChangeSurface(Surface *surface);
    Surface* GetCurrentSurface();
    Frame* ApplyAnimation(Animation* a);
    void AppendAnimation(Animation* a);

    GhostWidget *GetInScope() const;
    unsigned int GetID(GhostWidget *w) const;

private:
    GhostWidget* inScope;
    unsigned int idInScope;
    QVector<GhostWidget*> ghosts;
    QMap<GhostWidget*, Surface*> currentSurface;
    QMap<GhostWidget*, QList<Animation*>> currentAnimations;
};

#endif // GHOST_H
