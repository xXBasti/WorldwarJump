#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>


//! The world our game is based on. The fundamental stage. - WANG
class GameWorld: public QGraphicsView
{
public:
    // Member functions
    //! GameWorld Constructor
    GameWorld();

    // Member attributes
    QGraphicsScene * scene;

    //! Terrain, the playground for our battle units in form of an inner circle. - WANG
    QGraphicsEllipseItem *terrain;

};

#endif // GAMEWORLD_H
