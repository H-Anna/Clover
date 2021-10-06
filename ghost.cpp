#include "ghost.h"

Ghost::Ghost():
    inScope(new GhostWidget()),
    idInScope(0),
    ghosts(QVector<GhostWidget*>()),
    currentSurface(QMap<GhostWidget*, Surface*>()),
    currentAnimations(QMap<GhostWidget*, QList<Animation*>>())

{
    ghosts.append(inScope);
    inScope->show();
}

Ghost::~Ghost()
{
    for (auto &w: ghosts) {
        delete currentSurface.value(w);

        for (auto &it: currentAnimations.value(w)) {
            delete it;
        }
        delete w;
    }

    inScope = nullptr;
    delete inScope;
}

void Ghost::Hide()
{
    inScope->hide();
}

void Ghost::Show()
{
    inScope->show();
}

void Ghost::ChangeSurface(Surface *surface)
{
    currentSurface[inScope] = surface;
    inScope->displayedImage = QPixmap(surface->GetImage());
    inScope->update();
}

Surface *Ghost::GetCurrentSurface()
{
    return currentSurface[inScope];
}

Frame *Ghost::ApplyAnimation(Animation *a)
{
    auto f = a->GetNextFrame();

    if (f != nullptr) {
        AppendAnimation(a);
        inScope->displayedImage = QPixmap(f->GetImage());
        inScope->update();
    }

    return f;
}

void Ghost::AppendAnimation(Animation *a)
{
    if (currentAnimations.keys().contains(inScope)) {
       auto list = currentAnimations.value(inScope);

       if (!list.contains(a)) {

            list.append(a);
            currentAnimations[inScope] = list;
       }
    } else {
        auto list = QList<Animation*>({ a });
        currentAnimations.insert(inScope, list);
    }
}

GhostWidget *Ghost::GetInScope() const
{
    return inScope;
}

unsigned int Ghost::GetID(GhostWidget *w) const
{
    if (ghosts.contains(w))
        return ghosts.indexOf(w);

    return -1;
}
