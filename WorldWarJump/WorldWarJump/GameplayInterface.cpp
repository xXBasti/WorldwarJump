#include "GameplayInterface.h"
#include "physicscalc.h"
#include "gamesettings.h"

GameplayInterface::GameplayInterface(SoundPlayer * soundplayer)
{
    GameSettings * settings;
    int gameWorldSize = settings->getGameWorldSize();
    setSceneRect(0,0,gameWorldSize,gameWorldSize);

    physicsCalulator = new PhysicsCalc(soundplayer);

}



