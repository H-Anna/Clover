#ifndef FRAME_H
#define FRAME_H

#include <QString>

#include <surface_enums.h>

class Frame
{
public:
    Frame(int _id, const QString& _image, DrawMethod _drawMethod);

    QString PrintData();

    int GetId() const;
    QString GetImage() const;
    DrawMethod GetDrawMethod() const;

private:
    int id;
    QString image;
    DrawMethod drawMethod;

};

#endif // FRAME_H
