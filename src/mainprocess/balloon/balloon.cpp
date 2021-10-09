#include "balloon.h"

Balloon::Balloon(QVector<BalloonSurface*> _defaultBalloons):
    inScope(new BalloonWidget()),
    idInScope(0),
    defaultBalloons(_defaultBalloons)
{
    balloons.append(inScope);

    ConnectScope();

    auto b = defaultBalloons.at(0);

    inScope->show();
    inScope->ChangeBalloon(b->GetImage(), b->GetTopLeft(), b->GetBottomRight());
}

Balloon::~Balloon()
{
    while (!balloons.isEmpty()) {
        delete balloons.takeLast();
    }

    delete inScope;
}

void Balloon::ChangeBalloon(BalloonSurface *b)
{
    inScope->ChangeBalloon(b->GetImage(), b->GetTopLeft(), b->GetBottomRight());
}

void Balloon::ChangeScope(unsigned int id)
{

    if (idInScope == id)
        return;

    DisconnectScope();

    if (id >= balloons.length()) {

        id = balloons.length();
        balloons.append(new BalloonWidget());
        inScope = balloons.last();

    } else {
        inScope = balloons.at(id);
    }

    ConnectScope();

    idInScope = id;
    int _id = idInScope < defaultBalloons.length() ? idInScope : 0;
    auto b = defaultBalloons.at(_id);
    inScope->show();
    inScope->ChangeBalloon(b->GetImage(), b->GetTopLeft(), b->GetBottomRight());
}

void Balloon::ConnectScope()
{
    connect(this, SIGNAL(printTextSignal(const QString&)),
            inScope, SLOT(PrepareText(const QString&)));

    connect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));

}

void Balloon::DisconnectScope()
{
    disconnect(this, SIGNAL(printTextSignal(const QString&)),
            inScope, SLOT(PrepareText(const QString&)));

    disconnect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));

}

void Balloon::AppendHtml(const QString &text)
{
    if (inScope->textHolder != nullptr)
        inScope->textHolder->insertPlainText(text);
}

void Balloon::PrintBalloonContents()
{
    if (inScope->textHolder != nullptr)
        qDebug() << "INFO - BalloonWidget - textHolder contains:";
    qDebug() << inScope->textHolder->toPlainText();
}

void Balloon::ClearBalloon()
{
    if (inScope->textHolder != nullptr)
        inScope->textHolder->clear();
}

void Balloon::ChangeTextSpeed(unsigned int newSpeed)
{
    inScope->ChangeTextSpeed(newSpeed);
}

BalloonWidget *Balloon::GetInScope() const
{
    return inScope;
}

unsigned int Balloon::GetID(BalloonWidget *w) const
{
    if (balloons.contains(w))
        balloons.indexOf(w);

    return -1;
}
