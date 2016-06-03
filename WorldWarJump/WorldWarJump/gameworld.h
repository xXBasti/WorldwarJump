#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include "input.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include "GameplayInterface.h"

//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld();

    // Member attributes
    Input * input;
    GameplayInterface * scene;

    //! Terrain, the playground for our battle units in form of an inner circle. - WANG
    QGraphicsPixmapItem *terrain;
    int getGameWorldSize() const;
    void setGameWorldSize(int value);

    //Implemented pause and resume
    void pause();
    void resume();

private:
    //! Resolution of GameplayInterface
    int GameWorldSize;

};

#endif // GAMEWORLD_H
