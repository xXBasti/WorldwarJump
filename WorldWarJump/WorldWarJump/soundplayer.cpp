#include "soundplayer.h"
#include "gamesettings.h"

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

SoundPlayer::SoundPlayer()
{
    BGMplayer = new QMediaPlayer;
    BGMplaylist = new QMediaPlaylist;

    Jumpplayer = new QMediaPlayer;
    Jumpplayer->setMedia(QUrl("qrc:/sound/sound/jump.wav"));

    Shootplayer = new QMediaPlayer;
    Shootplayer->setMedia(QUrl("qrc:/sound/sound/shoot1.mp3"));

    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM.wav")); //Add menuBGM at pos 1.
    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM1.mp3")); //Add gameBGM at pos 2.



}

void SoundPlayer::playMenuBGM()
{
    if(!GameSettings::BGMMuted)
    {
        BGMplaylist->setCurrentIndex(1);
        BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        BGMplayer->setPlaylist(BGMplaylist);
        BGMplayer->play();
    }
}

void SoundPlayer::playGameBGM()
{
    if(!GameSettings::BGMMuted)
    {
        BGMplaylist->setPlaybackMode(QMediaPlaylist::Loop);
        //BGMplaylist->setCurrentIndex(1);
        BGMplaylist->next();
        BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    } else
    {
        BGMplayer->stop();
    }
}

void SoundPlayer::playJump()
{

    if(!GameSettings::SEMuted)Jumpplayer->play();

}

void SoundPlayer::playShoot()
{
    if(!GameSettings::SEMuted)Shootplayer->play();
}

void SoundPlayer::playHit()
{

}




