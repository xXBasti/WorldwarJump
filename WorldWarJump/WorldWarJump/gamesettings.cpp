#include "gamesettings.h"

GameSettings::GameSettings()
{
    settingsSceneAlreadyCreated = false;
    beforeGameSceneAlreadyCreated = false;
}

// static members are not defined in the constructor
int GameSettings::secondsToChangeLevel = 5;
int GameSettings::milisecondsBetweenBattleUnitShots = 1000;
int GameSettings::player1UnitCount = 1;
int GameSettings::player2UnitCount = 1;

int GameSettings::playerBlueShipCount = 0;
int GameSettings::playerBlueTankCount = 0;
int GameSettings::playerRedShipCount = 0;
int GameSettings::playerRedTankCount = 0;


int GameSettings::maxUnitsPerPlayer = 4;
int GameSettings::GameWorldSize = 800;
double GameSettings::gravity = 0.15;
int GameSettings::jumpCountForDestruction = 3;
double GameSettings::timeStep= 2;
int GameSettings::whichStage = 1;
bool GameSettings::frendlyfire=true;
bool GameSettings::unitCollision=false;
int GameSettings::meeleDmg= 0;

int GameSettings::BGMvolume= 25;
int GameSettings::SEvolume= 35;


bool GameSettings::BGMMuted = false;
bool GameSettings::SEMuted = false;

bool GameSettings::gameCreated = false;

int GameSettings::getPlayer1UnitCount() const
{
    return player1UnitCount;
}

void GameSettings::setPlayer1UnitCount(int value)
{
    if(0 <= value && value <= maxUnitsPerPlayer){
        player1UnitCount = value;
    }
}

int GameSettings::getPlayer2UnitCount() const
{
    return player2UnitCount;
}

void GameSettings::setPlayer2UnitCount(int value)
{
    if(0 <= value && value <= maxUnitsPerPlayer){
        player2UnitCount = value;
    }
}

int GameSettings::getWhichStage()
{
    return whichStage;
}

void GameSettings::setWhichStage(int value)
{
    whichStage = value;
}

bool GameSettings::getBeforeGameSceneAlreadyCreated() const
{
    return beforeGameSceneAlreadyCreated;
}

void GameSettings::setBeforeGameSceneAlreadyCreated(bool value)
{
    beforeGameSceneAlreadyCreated = value;
}

bool GameSettings::getSettingsSceneAlreadyCreated() const
{
    return settingsSceneAlreadyCreated;
}

void GameSettings::setSettingsSceneAlreadyCreated(bool value)
{
    settingsSceneAlreadyCreated = value;
}

int GameSettings::getGameWorldSize()
{
    return GameWorldSize;
}

double GameSettings::getGravity()
{
    return gravity;
}

void GameSettings::setGravityFromMenu(double value)
{
    gravity = value;
}

double GameSettings::getTimeStep()
{
    return timeStep;
}

void GameSettings::setTimeStep(double value)
{
    timeStep = value;
}

int GameSettings::getSecondsToChangeLevel()
{
    return secondsToChangeLevel;
}

void GameSettings::setSecondsToChangeLevel(int value)
{
    secondsToChangeLevel = value;
}

void GameSettings::setFrendlyFire(bool value){
    this->frendlyfire=value;
}

bool GameSettings::getFrendlyFire(){
    return frendlyfire;
}

void GameSettings::setMeeleDmg(int value){
    this->meeleDmg=value;
}

bool GameSettings::getBGMMuted()
{
    return BGMMuted;
}

void GameSettings::setBGMMuted(bool value)
{
    BGMMuted = value;
}

bool GameSettings::getSEMuted()
{
    return SEMuted;
}

void GameSettings::setSEMuted(bool value)
{
    SEMuted = value;
}

int GameSettings::getPlayerRedTankCount()
{
    return playerRedTankCount;
}

void GameSettings::setPlayerRedTankCount(int value)
{
    playerRedTankCount = value;
}

int GameSettings::getPlayerRedShipCount()
{
    return playerRedShipCount;
}

void GameSettings::setPlayerRedShipCount(int value)
{
    playerRedShipCount = value;
}

int GameSettings::getPlayerBlueShipCount()
{
    return playerBlueShipCount;
}

void GameSettings::setPlayerBlueShipCount(int value)
{
    playerBlueShipCount = value;
}

bool GameSettings::getUnitcollison()
{
    return unitCollision;
}

int GameSettings::getPlayerBlueTankCount()
{
    return playerBlueTankCount;
}

void GameSettings::setPlayerBlueTankCount(int value)
{
    playerBlueTankCount = value;
}

int GameSettings::getJumpCountForDestruction()
{
    return jumpCountForDestruction;
}

void GameSettings::setJumpCountForDestruction(int value)
{
    jumpCountForDestruction = value;
}

/**
 * @brief GameSettings::resetUnitCount sets all units count to 0.
 */
void GameSettings::resetUnitCount()
{
    GameSettings * settings;
    settings->setPlayer1UnitCount(0);
    settings->setPlayer2UnitCount(0);
    settings->setPlayerBlueShipCount(0);
    settings->setPlayerBlueTankCount(0);
    settings->setPlayerRedShipCount(0);
    settings->setPlayerRedTankCount(0);
}

int GameSettings::getBGMvolume()
{
    return BGMvolume;
}

void GameSettings::setBGMvolume(int value)
{
    BGMvolume = value;
}

int GameSettings::getSEvolume()
{
    return SEvolume;
}

void GameSettings::setSEvolume(int value)
{
    SEvolume = value;
}

int GameSettings::getMilisecondsBetweenBattleUnitShots()
{
    return milisecondsBetweenBattleUnitShots;
}

int GameSettings::getMeeleDmg(){
    return meeleDmg;
}
