#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

//!GameSettings saves the in-game setting... - WANG
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

private:
    static int player1UnitCount;
    static int player2UnitCount;
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
    static bool BGMMuted;
    static bool SEMuted;
};

#endif // GAMESETTINGS_H
