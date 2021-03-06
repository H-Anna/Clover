#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QMetaEnum>

class Frame: public QObject
{
    Q_OBJECT
public:
    enum DrawMethod
    {
        Base,
        Overlay,
        Clip,
        Replace,
        Insert
    };
    Q_ENUM(DrawMethod)

    Frame(unsigned int _id, const QString& _image, DrawMethod _drawMethod, unsigned int _ms);

    QString PrintData();

    unsigned int GetId() const;
    QString GetImage() const;
    DrawMethod GetDrawMethod() const;
    unsigned int GetMs() const;

private:
    unsigned int id;
    QString image;
    DrawMethod drawMethod;
    unsigned int ms;

};

#endif // FRAME_H
