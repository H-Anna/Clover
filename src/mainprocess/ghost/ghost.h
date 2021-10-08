#ifndef GHOST_H
#define GHOST_H

#include <ghostwidget.h>
#include <surface.h>

#include <QObject>

class Ghost: public QObject
{
    Q_OBJECT;
public:
    Ghost(unsigned int _layerCount = 1);
    ~Ghost();

    void Hide();
    void Show();
    Surface* GetCurrentSurface();
    GhostWidget *GetInScope() const;
    unsigned int GetID(GhostWidget *w) const;

signals:
    //void applyAnimationSignal(const QString& image, unsigned int layer, DrawMethod dm);
    void applyAnimationSignal(Animation* a, Frame* f);

public slots:
    void ChangeSurface(Surface *surface);
    //void ApplyAnimation(const QString &image, unsigned int layer, DrawMethod dm);
    void ApplyAnimation(Animation *a, Frame *f);

private:
    void AppendAnimation(Animation* a);


    GhostWidget* inScope;
    unsigned int idInScope;
    QVector<GhostWidget*> ghosts;
    QMap<GhostWidget*, Surface*> currentSurface;
    QMap<GhostWidget*, QList<Animation*>> currentAnimations;
};

#endif // GHOST_H
