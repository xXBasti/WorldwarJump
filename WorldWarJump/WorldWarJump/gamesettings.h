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

    int getWhichStage() const;
    void setWhichStage(int value);

    bool getBeforeGameSceneAlreadyCreated() const;
    void setBeforeGameSceneAlreadyCreated(bool value);

    bool getSettingsSceneAlreadyCreated() const;
    void setSettingsSceneAlreadyCreated(bool value);

private:
    int player1UnitCount;
    int player2UnitCount;
    int whichStage;
    bool beforeGameSceneAlreadyCreated;
    bool settingsSceneAlreadyCreated;
};

#endif // GAMESETTINGS_H
