#ifndef BALLOONSURFACE_H
#define BALLOONSURFACE_H

#include <QString>
#include <QPoint>

class BalloonSurface
{
public:
    BalloonSurface(unsigned int _id, const QString& _image, int TLX, int TLY, int BRX, int BRY);

    unsigned int GetId() const;
    const QString& GetImage() const;
    QPoint GetTopLeft() const;
    QPoint GetBottomRight() const;

private:
    unsigned int id;
    QString image;
    QPoint topLeft;
    QPoint bottomRight;
};

#endif // BALLOONSURFACE_H
