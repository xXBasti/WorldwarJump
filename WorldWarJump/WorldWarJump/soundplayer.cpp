#include "soundplayer.h"
#include "gamesettings.h"

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

SoundPlayer::SoundPlayer()
{
    BGMplayer = new QMediaPlayer;
    BGMplaylist = new QMediaPlaylist;

    SEplayer = new QMediaPlayer;
    SEplaylist = new QMediaPlaylist;

    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM.wav")); //Add menuBGM at pos 1.
    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM1.mp3")); //Add gameBGM at pos 2.

    SEplaylist->addMedia(QUrl("qrc:/sound/sound/jump.wav"));
    SEplaylist->addMedia(QUrl("qrc:/sound/sound/shoot.wav"));



}

void SoundPlayer::playMenuBGM()
{
    BGMplaylist->setCurrentIndex(1);
    BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    BGMplayer->setPlaylist(BGMplaylist);
    BGMplayer->play();
}

void SoundPlayer::playGameBGM()
{

    BGMplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    //BGMplaylist->setCurrentIndex(1);
    BGMplaylist->next();
    BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

}

void SoundPlayer::playJump()
{
    SEplaylist->setCurrentIndex(1);
    SEplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    SEplayer->setPlaylist(SEplaylist);
    SEplayer->play();

}

void SoundPlayer::playShoot()
{

}

void SoundPlayer::playHit()
{

}




