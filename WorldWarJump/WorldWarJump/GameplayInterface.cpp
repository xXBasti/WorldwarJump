#include "GameplayInterface.h"
#include "physicscalc.h"
#include "gamesettings.h"

GameplayInterface::GameplayInterface()
{
    GameSettings * settings;
    int gameWorldSize = settings->getGameWorldSize();
    setSceneRect(0,0,gameWorldSize,gameWorldSize);

    physicsCalulator = new PhysicsCalc();
}

