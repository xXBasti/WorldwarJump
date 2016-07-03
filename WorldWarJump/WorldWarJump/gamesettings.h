#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

/**
 * @brief GameSettings saves the in-game setting... - WANG
 *
 * All the game's variables are accessible as static member for other classes that include GameSettings 's header.
 **/
class GameSettings
{
public:
    GameSettings();
    int getPlayer1UnitCount() const;
    void setPlayer1UnitCount(int value);

    int getPlayer2UnitCount() const;
    void setPlayer2UnitCount(int value);


    bool getBeforeGameSceneAlreadyCreated() const;
    void setBeforeGameSceneAlreadyCreated(bool value);

    bool getSettingsSceneAlreadyCreated() const;
    void setSettingsSceneAlreadyCreated(bool value);

    static int getGameWorldSize();

    static int getWhichStage();
    static void setWhichStage(int value);

    static double getGravity();
    static void setGravityFromMenu(double value);

    static double getTimeStep();
    static void setTimeStep(double value);

    static int getSecondsToChangeLevel();
    static void setSecondsToChangeLevel(int value);

    bool getFrendlyFire();
    void setFrendlyFire(bool value);
    int getMeeleDmg();
    void setMeeleDmg(int value);
    static bool getBGMMuted();
    static void setBGMMuted(bool value);

    static bool getSEMuted();
    static void setSEMuted(bool value);

    static bool BGMMuted;
    static bool SEMuted;

    static int BGMvolume;
    static int SEvolume;

    static bool gameCreated;

    static int getPlayerRedTankCount();
    static void setPlayerRedTankCount(int value);

    static int getPlayerRedShipCount();
    static void setPlayerRedShipCount(int value);

    static int getPlayerBlueShipCount();
    static void setPlayerBlueShipCount(int value);
    static bool getUnitcollison();
    static int getPlayerBlueTankCount();
    static void setPlayerBlueTankCount(int value);

    static int getJumpCountForDestruction();
    static void setJumpCountForDestruction(int value);
    static void resetUnitCount();

    static int getBGMvolume();
    static void setBGMvolume(int value);

    static int getSEvolume();
    static void setSEvolume(int value);

    static int getMilisecondsBetweenBattleUnitShots();

private:
    static int player1UnitCount;
    static int player2UnitCount;

    static int playerRedTankCount;
    static int playerRedShipCount;
    static int playerBlueShipCount;
    static int playerBlueTankCount;
    static bool unitCollision;
    static int maxUnitsPerPlayer;
    static int GameWorldSize;
    static double gravity;
    static double timeStep;
    static int secondsToChangeLevel;
    static int whichStage;
    bool beforeGameSceneAlreadyCreated;
    bool settingsSceneAlreadyCreated;
    static bool frendlyfire;
    static int meeleDmg;
    static int jumpCountForDestruction;
    static int milisecondsBetweenBattleUnitShots;

};

#endif // GAMESETTINGS_H
