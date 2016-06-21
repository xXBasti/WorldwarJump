#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>


class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    SoundPlayer();
    QMediaPlayer *BGMplayer;
    QMediaPlayer *Jumpplayer;
    QMediaPlayer *Shootplayer;
    QMediaPlaylist *BGMplaylist;
    //QMediaPlaylist *SEplaylist;

    void playMenuBGM();
    void playGameBGM();
    void playJump();
    void playShoot();
    void playHit();

};

#endif // SOUNDPLAYER_H
