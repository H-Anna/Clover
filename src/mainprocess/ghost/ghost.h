#ifndef GHOST_H
#define GHOST_H

#include <ghostwidget.h>
#include <surface.h>

#include <QObject>

class Ghost: public QObject
{
    Q_OBJECT;
public:
    Ghost(QVector<Surface*> _defaultSurfaces, unsigned int _layerCount = 1);
    ~Ghost();

    void Hide();
    void Show();
    Surface* GetCurrentSurface();
    GhostWidget *GetInScope() const;
    unsigned int GetID(GhostWidget *w) const;

signals:
    void animateSignal(Animation* a, Frame* f);

public slots:
    void ChangeSurface(Surface *surface);
    void AnimateGhost(Animation *a, Frame *f);
    void ChangeScope(unsigned int id);

private:
    void AppendAnimation(Animation* a);

    GhostWidget* inScope;
    unsigned int idInScope;
    QVector<GhostWidget*> ghosts;
    QMap<GhostWidget*, Surface*> currentSurface;
    QMap<GhostWidget*, QList<Animation*>> currentAnimations;
    unsigned int layerCount;

    QVector<Surface*> defaultSurfaces;
};

#endif // GHOST_H
