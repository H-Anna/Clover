#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>

#include <frame.h>

class Animation
{
public:
    Animation(int _id, QString _name = "", Frequency _frequency = Frequency::Never);

    QString PrintData();

    unsigned int GetId() const;
    const QString& GetName() const;
    bool HasName() const;
    Frequency GetFrequency() const;
    QVector<Frame*> GetFrames() const;

    void AddFrame(const QString& _image, DrawMethod _drawMethod, unsigned int _ms);
    Frame* GetNextFrame();

private:

    unsigned int id;
    QString name;
    Frequency frequency;

    unsigned int frameCursor;
    QVector<Frame*> frames;

};

#endif // ANIMATION_H
