#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <QString>
#include <QPoint>

class Hotspot
{
public:
    Hotspot(const QString& _name, int TLX, int TLY, int BRX, int BRY, Qt::CursorShape _cursor);

    const QString &getName() const;
    QPoint getTopLeft() const;
    QPoint getBottomRight() const;
    Qt::CursorShape getCursor() const;

private:
    QString name;
    QPoint topLeft;
    QPoint bottomRight;
    Qt::CursorShape cursor;
};

#endif // HOTSPOT_H
