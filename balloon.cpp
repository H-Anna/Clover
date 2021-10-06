#include "balloon.h"

Balloon::Balloon()
{
    inScope = new BalloonWidget();
    balloons.insert(0,inScope);

    connect(this, SIGNAL(printTextSignal(const QString&)),
            inScope, SLOT(prepareText(const QString&)));

    connect(inScope, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTextPrintSignal()));

    inScope->show();
}

Balloon::~Balloon()
{
    for (auto &key: balloons.keys()) {
        delete balloons[key];
    }

    inScope = nullptr;
    delete inScope;
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
    return balloons.key(w, -1);
}
