#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include<QMediaPlayer>


class SoundPlayer : public QMediaPlayer
{
public:
    SoundPlayer();

    void playMenuBGM();
    void playGameBGM();

public slots:
    void playJump();
    void playShoot();
    void playHit();
    void playBounce();
    void playClicked();
    void muteSoundEffects();
    void muteBGM();
};

#endif // SOUNDPLAYER_H
