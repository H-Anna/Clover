#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <hotspotvariable.h>

#include <QString>
#include <QPoint>
#include <QList>

class Hotspot
{
public:
    Hotspot(const QString& _name, int TLX, int TLY, int BRX, int BRY, Qt::CursorShape _cursor);

    const QString &getName() const;
    QPoint getTopLeft() const;
    QPoint getBottomRight() const;
    Qt::CursorShape getCursor() const;


    void AddVariable(const QString _name, HotspotVariable::Interaction _interaction);

    QList<HotspotVariable *> GetVariables() const;

private:
    QString name;
    QPoint topLeft;
    QPoint bottomRight;
    Qt::CursorShape cursor;
    QList<HotspotVariable*> variables;
};

#endif // HOTSPOT_H
