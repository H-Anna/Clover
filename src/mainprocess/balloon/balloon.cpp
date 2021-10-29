#include "balloon.h"

Balloon::Balloon(QVector<BalloonSurface*> _defaultBalloons):
    inScope(new BalloonWidget()),
    idInScope(0),
    defaultBalloons(_defaultBalloons)
{
    balloons.append(inScope);
}

Balloon::~Balloon()
{
    while (!balloons.isEmpty()) {
        delete balloons.takeLast();
    }

    balloons.clear();

    while (!defaultBalloons.isEmpty()) {
        delete defaultBalloons.takeLast();
    }

    defaultBalloons.clear();

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

        /// Create new balloon

        id = balloons.length();
        balloons.append(new BalloonWidget());
        inScope = balloons.last();

        int _id = idInScope < defaultBalloons.length() ? idInScope : 0;
        auto b = defaultBalloons.at(_id);
        inScope->show();
        ChangeBalloon(b);

    } else {
        inScope = balloons.at(id);
    }

    idInScope = id;

    ConnectScope();


}

void Balloon::ConnectScope()
{
    connect(this, SIGNAL(printTextSignal(QString)),
            inScope, SLOT(PrepareText(QString)));

    connect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));

    /// The following signals should not be disconnected when the scope is switched

    connect(this, SIGNAL(timeoutSignal()),
            inScope, SLOT(PrepareTimeout()));

}

void Balloon::DisconnectScope()
{
    disconnect(this, SIGNAL(printTextSignal(QString)),
            inScope, SLOT(PrepareText(QString)));

    disconnect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));
}

void Balloon::AppendHtml(const QString &text)
{
    if (inScope->textHolder != nullptr)
    {
        inScope->show();
        inScope->textHolder->insertPlainText(text);
    }
}

void Balloon::PrintBalloonContents()
{
    if (inScope->textHolder != nullptr)
        qDebug() << "INFO - BalloonWidget - textHolder contains:" << inScope->textHolder->toPlainText();
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

void Balloon::Reset()
{
    DisconnectScope();
    inScope = nullptr;

    while (!balloons.isEmpty()) {
        balloons.takeLast()->deleteLater();
    }

    balloons.clear();

    inScope = new BalloonWidget();
    ConnectScope();

    balloons.append(inScope);
    auto b = defaultBalloons.at(0);
    ChangeBalloon(b);

}

BalloonWidget *Balloon::GetInScope() const
{
    return inScope;
}

unsigned int Balloon::GetID(BalloonWidget *w) const
{
    if (balloons.contains(w))
        return balloons.indexOf(w);

    return -1;
}
