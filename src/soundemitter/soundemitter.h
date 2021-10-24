#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaContent>

class SoundEmitter: public QObject
{
    Q_OBJECT
public:

    SoundEmitter();
    ~SoundEmitter();
    bool LoadSounds(QJsonObject* json, const QString& imgPath);

public slots:

    void Play(const QString& name, int loops = 0);
    void Stop();
//    void Pause();
//    void Resume();
//    void MuteUnmute();

private:

    class MediaData
    {
    public:
        MediaData() = default;
        MediaData(const QString& _name, const QString& _type, const QString& _location):
            name(_name), type(_type), location(_location) {}

        QString name;
        QString type;
        QString location;

    };

    QMediaPlayer* player;
    //QMap<QString, QSound*> sounds; ///TODO: use QSoundEffect for sfx instead of the player?
    QMap<QString, MediaData> media;

};

#endif // SOUNDEMITTER_H
