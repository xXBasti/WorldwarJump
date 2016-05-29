#include "gameworld.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>


GameWorld::GameWorld()
{
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,700,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(700,700);

    terrain = new QGraphicsEllipseItem(10,10,680,680);
    scene->addItem(terrain);


}
