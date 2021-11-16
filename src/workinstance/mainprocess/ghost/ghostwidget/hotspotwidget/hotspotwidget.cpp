#include "hotspotwidget.h"

HotspotWidget::HotspotWidget(VariableStore* varStore, QList<HotspotVariable *> _variables, QWidget *parent):
    variables(_variables),
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMouseTracking(true);
    setAutoFillBackground(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    setPalette(p);

    /// TODO: connect a TalkManager signal here

//    connect(this, SIGNAL(hotspotTalkSignal(QString,QString)),
//            varStore->GetMember("TalkManager"), SLOT(AnchorTalk(QString,QString)));

    connect(this, SIGNAL(incrementSignal(QString)),
            varStore, SLOT(increment(QString)));


    showMaximized();
}

void HotspotWidget::mouseMoveEvent(QMouseEvent *event)
{
    for (const auto &v: qAsConst(variables))
    {
        if (v->GetInteraction() == HotspotVariable::Interaction::MouseMove)
        {
            emit incrementSignal(v->GetName());
        }
    }
}

void HotspotWidget::wheelEvent(QWheelEvent *event)
{
    for (const auto &v: qAsConst(variables))
    {
        if (v->GetInteraction() == HotspotVariable::Interaction::MouseWheel)
        {
            emit incrementSignal(v->GetName());
        }
    }
}

void HotspotWidget::mousePressEvent(QMouseEvent *event)
{
    for (const auto &v: qAsConst(variables))
    {
        if (v->GetInteraction() == HotspotVariable::Interaction::MouseClick)
        {
            emit incrementSignal(v->GetName());
        }
    }


}
