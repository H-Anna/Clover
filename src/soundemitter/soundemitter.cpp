#include "soundemitter.h"

SoundEmitter::SoundEmitter()
{
    player = new QMediaPlayer(this);
    player->setVolume(100);
}

SoundEmitter::~SoundEmitter()
{
//    QMapIterator s(sounds);
//    while (s.hasNext()) {
//        delete s.value();
//    }

    delete player;
}

bool SoundEmitter::LoadSounds(QJsonObject *json, const QString &path)
{
    QJsonArray soundArray = json->value("content").toArray();

    if (soundArray.isEmpty())
        return false;

    for (int i = 0; i < soundArray.count(); i++) {

        auto obj = soundArray.at(i).toObject();
        QString name = obj.value("name").toString();
        QString type = obj.value("type").toString();
        QString location = obj.value("location").toString();
        //sounds[name] = new QSound(path + location);

        if (type == "file")
            location = path + location;

        media[name] = MediaData(name, type, location);
    }

    return true;
}


/// Supported formats: wav and mp3. TODO: work on a solution to support ogg

void SoundEmitter::Play(const QString &name, int loops)
{
    if (media.contains(name)) {

        auto md = media.value(name);
        QUrl src;

        if (md.type == "file") {

            src = QUrl::fromLocalFile(md.location);

        } else if (md.type == "url") {
            /// Please provide a direct link to an audio file, ending in .mp3 or .wav.
            /// Youtube links etc. will not work.

            src = QUrl(md.location);
        }

        player->setMedia(src);
        player->play();

        qDebug().noquote() << QString("INFO - SoundEmitter - Played %1").arg(md.location);

    } else {
        qDebug().noquote() << QString("WARNING - SoundEmitter - Sound with name %1 doesn't exist").arg(name);
    }



//    if (sounds.contains(name)) {

//        sounds.value(name)->setLoops(loops);
//        sounds.value(name)->play();

//        qDebug().noquote() << QString("INFO - SoundEmitter - Played %1").arg(sounds.value(name)->fileName());

//    } else {
//        qDebug().noquote() << QString("WARNING - SoundEmitter - Sound with name %1 doesn't exist").arg(name);
//    }
}

void SoundEmitter::Stop()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        player->stop();
    }


//    if (sounds.contains(name)) {

//        sounds.value(name)->stop();

//        qDebug().noquote() << QString("INFO - SoundEmitter - Played %1").arg(sounds.value(name)->fileName());

//    } else {
//        qDebug().noquote() << QString("WARNING - SoundEmitter - Sound with name %1 doesn't exist").arg(name);
//    }
}
