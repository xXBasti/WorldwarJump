#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include "GameplayInterface.h"


//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld();

    // Member attributes
    GameplayInterface * scene;

};

#endif // GAMEWORLD_H
