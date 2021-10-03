#ifndef ANIMATION_H
#define ANIMATION_H

#include <QList>
#include <QMap>

#include <frame.h>

class Animation
{
public:
    Animation(int _id, DrawMethod _drawMethod);

    QString PrintData();

    int GetId() const;
    QMap<int, Frame*> GetFrames() const;
    DrawMethod GetDrawMethod() const;

    void AddFrame(int _id, const QString& _image, DrawMethod _drawMethod);

private:

    int id;
    DrawMethod drawMethod;

    QMap<int, Frame*> frameIDMap;

};

#endif // ANIMATION_H
