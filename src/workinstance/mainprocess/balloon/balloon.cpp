#include "balloon.h"

Balloon::Balloon(VariableStore* _varStore, QVector<BalloonSurface*> _defaultBalloons):
    varStore(_varStore),
    inScope(new BalloonWidget(_varStore)),
    idInScope(0),
    defaultBalloons(_defaultBalloons)
{
    balloons.append(inScope);
    ConnectScope();
}

Balloon::~Balloon()
{
    while (!balloons.isEmpty()) {
        delete balloons.takeLast();
    }

    balloons.clear();

//    while (!defaultBalloons.isEmpty()) {
//        delete defaultBalloons.takeLast();
//    }

    defaultBalloons.clear();

    //delete inScope;
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
        balloons.append(new BalloonWidget(varStore));
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
    connect(this, &Balloon::printTextSignal,
            inScope, &BalloonWidget::PrepareText);

    connect(inScope, &BalloonWidget::finishedTextPrintSignal,
            this, &Balloon::finishedTextPrintSignal);

    /// The following signals should not be disconnected when the scope is switched

    connect(this, &Balloon::timeoutSignal,
            inScope, &BalloonWidget::PrepareTimeout);

    connect(this, &Balloon::setTimeoutSignal,
            inScope, &BalloonWidget::SetTimeout);

}

void Balloon::DisconnectScope()
{
    disconnect(this, &Balloon::printTextSignal,
            inScope, &BalloonWidget::PrepareText);

    disconnect(inScope, &BalloonWidget::finishedTextPrintSignal,
            this, &Balloon::finishedTextPrintSignal);
}

void Balloon::AppendHtml(const QString &text)
{
    inScope->AppendHtml(text);
}

void Balloon::PrintBalloonContents()
{
    inScope->PrintContents();
}

void Balloon::ClearBalloon()
{
    inScope->ClearBalloon();
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
        auto b = balloons.takeLast();
        b->blockSignals(true);
        b->deleteLater();
    }

    balloons.clear();

    inScope = new BalloonWidget(varStore);
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
