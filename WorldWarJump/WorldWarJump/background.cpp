#include "background.h"

BackGround::BackGround(GameSettings *settings, QTimer *backGroundRotationTimer)
{
    gameWorldSize = 800;
    stage = settings->getWhichStage();
    switch(stage)
    {
    case 2:
        backGroundRotationTimer->stop();
        this->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/Battlefield_Background.png"));
        this->setRotation(0);
        break;
    case 1:
        this->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/weltallBackground.png"));
        this->setTransformOriginPoint(gameWorldSize/2, gameWorldSize/2);
        backGroundRotationTimer->start(20);
        break;
    }
}
