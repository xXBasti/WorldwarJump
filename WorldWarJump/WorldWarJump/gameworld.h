#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include "input.h"


//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld();

    // Member attributes
    QGraphicsScene * scene;
    Input * input;

};

#endif // GAMEWORLD_H
