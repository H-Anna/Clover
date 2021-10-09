#include "balloonsurface.h"

BalloonSurface::BalloonSurface(unsigned int _id, const QString &_image, int TLX, int TLY, int BRX, int BRY):
    id(_id),
    image(_image),
    topLeft(QPoint(TLX,TLY)),
    bottomRight(QPoint(BRX,BRY))
{

}

 unsigned int BalloonSurface::GetId() const
{
     return id;
 }

 const QString &BalloonSurface::GetImage() const
 {
     return image;
 }

 QPoint BalloonSurface::GetTopLeft() const
 {
     return topLeft;
 }

 QPoint BalloonSurface::GetBottomRight() const
 {
     return bottomRight;
 }
