#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>

/** @brief This is our sound system. - Wang and Can
 */

class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    SoundPlayer();
    QMediaPlayer *BGMplayer;
    QMediaPlayer *Jumpplayer;
    QMediaPlayer *ShootProjectilePlayer;
    QMediaPlaylist *Projectileplaylist;

    QMediaPlayer *ShootTauntplayer;
    QMediaPlaylist *BGMplaylist;
    QMediaPlayer *Hitplayer;

    //QMediaPlaylist *SEplaylist;

    void playProjectileTypeShoot(int type);
    void playMenuBGM();
    void playGameBGM();
    void playJump();
    void playHit();

    int randomIndex;

};

#endif // SOUNDPLAYER_H
