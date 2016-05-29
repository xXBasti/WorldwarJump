#include "gameworld.h"
#include <QGraphicsScene>

GameWorld::GameWorld()
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(1024,768);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
