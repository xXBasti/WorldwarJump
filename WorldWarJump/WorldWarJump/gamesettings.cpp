#include "gamesettings.h"

GameSettings::GameSettings()
{
    player1UnitCount = 1;
    player2UnitCount = 1;
    whichStage = 1;
    settingsSceneAlreadyCreated = false;
    beforeGameSceneAlreadyCreated = false;
}

int GameSettings::getPlayer1UnitCount() const
{
    return player1UnitCount;
}

void GameSettings::setPlayer1UnitCount(int value)
{
    player1UnitCount = value;
}

int GameSettings::getPlayer2UnitCount() const
{
    return player2UnitCount;
}

void GameSettings::setPlayer2UnitCount(int value)
{
    player2UnitCount = value;
}

int GameSettings::getWhichStage() const
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

