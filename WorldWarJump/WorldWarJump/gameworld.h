#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include <QTimer>
#include "input.h"
#include <QGraphicsScene>
//#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include "GameplayInterface.h"
#include "gamesettings.h"
#include "soundplayer.h"
#include <QDebug>

class Terrain;

enum Player {player1, player2};
enum ProjectileType {missile, balistic, ray, scrap};
enum unitType{Tank,Soldier,Ship};


//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
    Q_OBJECT
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld(SoundPlayer *soundplayer);
    ~GameWorld();

    // Member attributes
    Terrain * terrain;
    Input * input;
    GameplayInterface * scene;
    QTimer * levelSwitchTimer;
    QTimer * backGroundRotationTimer;
    QGraphicsPixmapItem *background;

    void setGameWorldSize(int value);

    // Implemented pause and resume
    void pause();
    void resume();

    //for sound
    SoundPlayer *soundpointer;

private:
    //! defines the resolution of GameplayInterface
    int gameWorldSize;
    GameSettings * settings;
    void addUnits();
public slots:
    //void changeLevel();
    void playeronewins();
    void playertwowins();
    //void setBar(int value);
    void rotateBackground();
signals:
    void playeronewinsSignal();
    void playertwowinsSignal();


};

#endif // GAMEWORLD_H
