#include "ghost.h"

Ghost::Ghost()
{
    inScope = new GhostWidget();
    ghosts.insert(0,inScope);
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

void Ghost::ChangeSurface(const QString &path)
{
    inScope->displayedImage = QPixmap(path);
    inScope->update();
}

GhostWidget *Ghost::GetInScope() const
{
    return inScope;
}

int Ghost::GetID(GhostWidget *w) const
{
    return ghosts.key(w, -1);
}

