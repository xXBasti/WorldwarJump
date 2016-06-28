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
    Shootplayer->setVolume(30);

    Hitplayer = new QMediaPlayer;
    Hitplayer->setMedia(QUrl("qrc:/sound/sound/BigExplosion_cut.mp3"));
    Hitplayer->setVolume(80);

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
        BGMplayer->setVolume(20);
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

    if(!GameSettings::SEMuted){

        Jumpplayer->setMedia(QUrl("qrc:/sound/sound/jump.wav"));
        Jumpplayer->play();
        Hitplayer->play();}

}

void SoundPlayer::playShoot()
{
    if(!GameSettings::SEMuted){
        //Random number between 0-9
        int random_var = (rand()%10);
        if(random_var == 1){

            Shootplayer->setVolume(30);
            Shootplayer->setMedia(QUrl("qrc:/sound/sound/shoot1.mp3"));
            Shootplayer->play();

        }else{
            Shootplayer->setVolume(80);
            Shootplayer->setMedia(QUrl("qrc:/sound/sound/ShootCannon_cut.mp3"));
            Shootplayer->play();
        }
    }
}

void SoundPlayer::playHit()
{

    if(!GameSettings::SEMuted){
        Hitplayer->setMedia(QUrl("qrc:/sound/sound/BigExplosion_cut.mp3"));
        Hitplayer->play();
    }
}




