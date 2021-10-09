#include "balloon.h"

Balloon::Balloon()
{
    inScope = new BalloonWidget();
    balloons.append(inScope);

    connect(this, SIGNAL(printTextSignal(const QString&)),
            inScope, SLOT(PrepareText(const QString&)));

    connect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));

    inScope->show();
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
