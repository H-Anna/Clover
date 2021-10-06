#include "ghost.h"

Ghost::Ghost():
    inScope(new GhostWidget()),
    idInScope(0),
    ghosts(QMap<unsigned int, GhostWidget*>()),
    currentSurface(QMap<unsigned int, Surface*>()),
    currentAnimations(QMap<unsigned int, QList<Animation*>>())

{
    ghosts.insert(idInScope,inScope);
    inScope->show();
}

Ghost::~Ghost()
{
    for (auto &key: ghosts.keys()) {
        delete ghosts[key];
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
    currentSurface[idInScope] = surface;
    inScope->displayedImage = QPixmap(surface->GetImage());
    inScope->update();
}

Surface *Ghost::GetCurrentSurface()
{
    return currentSurface[idInScope];
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
    if (currentAnimations.keys().contains(idInScope)) {
       auto list = currentAnimations.value(idInScope);

       if (!list.contains(a)) {

            list.append(a);
            currentAnimations[idInScope] = list;
       }
    } else {
        auto list = QList<Animation*>({ a });
        currentAnimations.insert(idInScope, list);
    }
}

GhostWidget *Ghost::GetInScope() const
{
    return inScope;
}

unsigned int Ghost::GetID(GhostWidget *w) const
{
    return ghosts.key(w, -1);
}

