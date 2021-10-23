#include "ghost.h"

Ghost::Ghost(QVector<Surface*> _defaultSurfaces, unsigned int _layerCount):
    inScope(new GhostWidget(_layerCount)),
    idInScope(0),
    ghosts(QVector<GhostWidget*>()),
    currentSurface(QMap<GhostWidget*, Surface*>()),
    currentAnimations(QMap<GhostWidget*, QList<Animation*>>()),
    layerCount(_layerCount),
    defaultSurfaces(_defaultSurfaces)

{
    ghosts.append(inScope);
    ChangeSurface(defaultSurfaces.at(0));
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
    inScope->SetSurface(surface->GetElements());
    inScope->SetHotspots(surface->GetHotspots());
}

Surface *Ghost::GetCurrentSurface() const
{
    return currentSurface.value(inScope);
}

void Ghost::AnimateGhost(Animation* a, Frame* f)
{
    AppendAnimation(a);
    inScope->SetAnimation(f->GetImage(), a->GetLayer(), f->GetDrawMethod());
}

void Ghost::ChangeScope(unsigned int id)
{
    if (idInScope == id)
        return;

    if (id >= ghosts.length()) {

        /// Create new ghost

        id = ghosts.length();
        ghosts.append(new GhostWidget(layerCount));
        inScope = ghosts.last();

        idInScope = id;

        int _id = idInScope < defaultSurfaces.length() ? idInScope : 0;
        inScope->SetSurface(defaultSurfaces.at(_id)->GetElements());
        inScope->show();

    } else {

        inScope = ghosts.at(id);
    }
}

void Ghost::AppendAnimation(Animation *a)
{
    if (currentAnimations.contains(inScope)) {
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
