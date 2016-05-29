#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
<<<<<<< HEAD
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
=======
#include "GameplayInterface.h"
>>>>>>> 074cb69799db12d77dd92167216db74e3eb3cb19


//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld();

    // Member attributes
    GameplayInterface * scene;

    //! Terrain, the playground for our battle units in form of an inner circle. - WANG
    QGraphicsEllipseItem *terrain;

};

#endif // GAMEWORLD_H
