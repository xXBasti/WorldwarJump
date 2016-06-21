#include "soundplayer.h"
#include "gamesettings.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>

SoundPlayer::SoundPlayer()
{
    this->addMedia(QUrl("qrc:/sound/sound/gameBGM.wav"));
    this->setCurrentIndex(1);
    this->setPlaybackMode(QMediaPlaylist::Loop);
}
