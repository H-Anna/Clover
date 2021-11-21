#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>

#include <frame.h>

class Animation: public QObject
{
    Q_OBJECT
public:
    enum Frequency
    {
        Never = 0,
        Always = 1,
        Loop = 2
    };
    Q_ENUM(Frequency)

    Animation(int _id, QString _name = "", Frequency _frequency = Frequency::Never, unsigned int _layer = 0);
    ~Animation();

    QString PrintData();

    unsigned int GetId() const;
    const QString& GetName() const;
    bool HasName() const;
    Frequency GetFrequency() const;
    QVector<Frame*> GetFrames() const;
    unsigned int GetLayer() const;

    void AddFrame(const QString& _image, Frame::DrawMethod _drawMethod, unsigned int _ms);
    Frame* GetNextFrame();
    void Reset();

private:

    unsigned int id;
    QString name;
    Frequency frequency;
    unsigned int layer;

    unsigned int frameCursor;
    QVector<Frame*> frames;

};

#endif // ANIMATION_H
