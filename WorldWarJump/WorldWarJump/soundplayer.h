#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>


class SoundPlayer : public QMediaPlaylist
{
    Q_OBJECT
public:
    SoundPlayer();
};

#endif // SOUNDPLAYER_H
