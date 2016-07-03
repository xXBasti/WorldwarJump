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
#include <QLabel>
#include <QTimer>

class Terrain;

enum Player {player1, player2};
enum ProjectileType {missile, balistic, ray};
enum unitType{Tank,Soldier,Ship};




/**
 * @brief container class for Terrain, Input and GameplayInterface.
 *
 * Details: GameWorld contains classes that need to communicate with each other and enables connect() functions between them.
 * It also contains a QTimer to make the background rotate.
 */
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
    QTimer * backGroundRotationTimer;
    QGraphicsPixmapItem *background;

    void setGameWorldSize(int value);

    // Implemented pause and resume
    void pause();
    void resume();

    //for sound
    SoundPlayer *soundpointer;

private:
    //! fetches the resolution of GameplayInterface
    int gameWorldSize;
    GameSettings * settings;
    void addUnits();
    QLabel* display;
    QTimer* meeleTimer;
public slots:
    //void changeLevel();
    void playeronewins();
    void playertwowins();
    //void setBar(int value);
    void rotateBackground();
signals:
    void playerOneWinsSignal();
    void playerTwoWinsSignal();
public slots:
    void displayMeele();


    void hideMeele();
};

#endif // GAMEWORLD_H
