#ifndef HOTSPOTVARIABLE_H
#define HOTSPOTVARIABLE_H

#include <QObject>
#include <QString>

class HotspotVariable: public QObject
{
    Q_OBJECT
public:
    enum Interaction {
        MouseMove = 0,
        MouseClick = 1,
        DoubleClick = 2,
        MouseWheel = 3
    };
    Q_ENUM(Interaction)

    //HotspotVariable(const QString _name, Interaction _interaction, unsigned int _threshold = 0);
    HotspotVariable(const QString _name, Interaction _interaction);

    const QString &GetName() const;
    const Interaction GetInteraction() const;
    //const unsigned int GetThreshold() const;

private:
    QString name;
    Interaction interaction;
//    unsigned int threshold;
};

#endif // HOTSPOTVARIABLE_H
