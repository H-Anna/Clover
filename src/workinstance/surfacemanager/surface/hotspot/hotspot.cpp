#include "hotspot.h"

Hotspot::Hotspot(const QString &_name, int TLX, int TLY, int BRX, int BRY, Qt::CursorShape _cursor):
    name(_name),
    topLeft(TLX, TLY),
    bottomRight(BRX, BRY),
    cursor(_cursor)
{

}

const QString &Hotspot::getName() const
{
    return name;
}

QPoint Hotspot::getTopLeft() const
{
    return topLeft;
}

QPoint Hotspot::getBottomRight() const
{
    return bottomRight;
}

Qt::CursorShape Hotspot::getCursor() const
{
    return cursor;
}

void Hotspot::AddVariable(const QString _name, HotspotVariable::Interaction _interaction)
{
    variables.append(new HotspotVariable(_name, _interaction));
}

QList<HotspotVariable *> Hotspot::GetVariables() const
{
    return variables;
}
