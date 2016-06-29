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


    ShootProjectilePlayer = new QMediaPlayer;
    Projectileplaylist = new QMediaPlaylist;
    Projectileplaylist->addMedia(QUrl("qrc:/sound/sound/ShootRocket2_cut.mp3"));//2 options
    Projectileplaylist->addMedia(QUrl("qrc:/sound/sound/ShootCannon_cut.mp3"));
    Projectileplaylist->addMedia(QUrl("qrc:/sound/sound/ShootRay_cut.mp3"));
    Projectileplaylist->addMedia(QUrl("qrc:/sound/sound/ShootScrap_cut.mp3"));


    ShootTauntplayer = new QMediaPlayer;
    ShootTauntplayer->setMedia(QUrl("qrc:/sound/sound/shoot1.mp3"));
    ShootTauntplayer->setVolume(30);

    Hitplayer = new QMediaPlayer;
    Hitplayer->setMedia(QUrl("qrc:/sound/sound/BigExplosion_cut.mp3"));
    Hitplayer->setVolume(80);

    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM.wav")); //Add menuBGM at pos 1.
    BGMplaylist->addMedia(QUrl("qrc:/sound/sound/gameBGM1.mp3")); //Add gameBGM at pos 2.

    this->randomIndex = 20;

}

void SoundPlayer::playProjectileTypeShoot(int type)
{
    if(!GameSettings::SEMuted){
        //Random number between 0-19 and always growing , so we hear the taunt less and less
        int random_var = (rand()%(this->randomIndex));
        this->randomIndex += 5;
        if(randomIndex > 1000) randomIndex = 40;
        if(random_var == 4) type = 4;
        switch(type){
            // Missile
            case 0:
                ShootProjectilePlayer->stop();
                Projectileplaylist->setCurrentIndex(0);
                ShootProjectilePlayer->setMedia(Projectileplaylist->currentMedia());
                ShootProjectilePlayer->setVolume(GameSettings::SEvolume+15);//20 if rocket1 50 if rocket 2
                ShootProjectilePlayer->play();
                break;
            // Balistic
            case 1:
                ShootProjectilePlayer->stop();
                Projectileplaylist->setCurrentIndex(1);
                ShootProjectilePlayer->setMedia(Projectileplaylist->currentMedia());
                ShootProjectilePlayer->setVolume(GameSettings::SEvolume);
                ShootProjectilePlayer->play();
                break;
            // Ray
            case 2:
                ShootProjectilePlayer->stop();
                Projectileplaylist->setCurrentIndex(2);
                ShootProjectilePlayer->setMedia(Projectileplaylist->currentMedia());
                ShootProjectilePlayer->setVolume(GameSettings::SEvolume+15);
                ShootProjectilePlayer->play();
                break;
            // Scrap
            case 3:
                ShootProjectilePlayer->stop();
                Projectileplaylist->setCurrentIndex(3);
                ShootProjectilePlayer->setMedia(Projectileplaylist->currentMedia());
                ShootProjectilePlayer->setVolume(GameSettings::SEvolume+45);
                ShootProjectilePlayer->play();
                break;
            // Taunt
            case 4:
                ShootTauntplayer->stop();
                ShootTauntplayer->play();
                break;
        }

    }

}

void SoundPlayer::playMenuBGM()
{
    if(!GameSettings::BGMMuted)
    {
        BGMplaylist->setCurrentIndex(1);
        BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        BGMplayer->setPlaylist(BGMplaylist);
        BGMplayer->setVolume(GameSettings::BGMvolume);
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

        Jumpplayer->stop();
        Jumpplayer->setVolume(GameSettings::SEvolume-15);
        Jumpplayer->play();
    }

}


void SoundPlayer::playHit()
{

    if(!GameSettings::SEMuted){
        Hitplayer->stop();
        Hitplayer->setVolume(GameSettings::SEvolume);
        Hitplayer->play();
    }
}




