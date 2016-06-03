#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include "input.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include "GameplayInterface.h"
#include "terrain.h"

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

    int getGameWorldSize() const;
    void setGameWorldSize(int value);

    // Implemented pause and resume
    void pause();
    void resume();

private:
    //! defines the resolution of GameplayInterface
    int GameWorldSize;

};

#endif // GAMEWORLD_H
