#include "gamesettings.h"

GameSettings::GameSettings()
{
    settingsSceneAlreadyCreated = false;
    beforeGameSceneAlreadyCreated = false;
}

// static members are not defined in the constructor
int GameSettings::secondsToChangeLevel = 5;
int GameSettings::player1UnitCount = 1;
int GameSettings::player2UnitCount = 1;

int GameSettings::playerBlueShipCount = 1;
int GameSettings::playerBlueTankCount = 1;
int GameSettings::playerRedShipCount = 1;
int GameSettings::playerRedTankCount = 1;


int GameSettings::maxUnitsPerPlayer = 4;
int GameSettings::GameWorldSize = 800;
double GameSettings::gravity = 0.15;
double GameSettings::timeStep= 2;
int GameSettings::whichStage = 0;
bool GameSettings::frendlyfire=true;
int GameSettings::meeleDmg=10;

bool GameSettings::BGMMuted = true;
bool GameSettings::SEMuted = true;


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

int GameSettings::getPlayerBlueTankCount()
{
    return playerBlueTankCount;
}

void GameSettings::setPlayerBlueTankCount(int value)
{
    playerBlueTankCount = value;
}

int GameSettings::getMeeleDmg(){
    return meeleDmg;
}
