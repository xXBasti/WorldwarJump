#include "GameplayInterface.h"
#include "physicscalc.h"
#include "gamesettings.h"

/**
 * @brief GameplayInterface::GameplayInterface
 * @param soundplayer
 *
 * static values for the scene's size are fetched from GameSettings
 */
GameplayInterface::GameplayInterface(SoundPlayer * soundplayer)
{
    GameSettings * settings;
    int gameWorldSize = settings->getGameWorldSize();
    setSceneRect(0,0,gameWorldSize,gameWorldSize);

    physicsCalulator = new PhysicsCalc(soundplayer);

}



