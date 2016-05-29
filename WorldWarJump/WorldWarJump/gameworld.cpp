#include "gameworld.h"
#include <QGraphicsScene>
<<<<<<< HEAD
#include <QGraphicsEllipseItem>

=======
#include "GameplayInterface.h"
>>>>>>> 074cb69799db12d77dd92167216db74e3eb3cb19

GameWorld::GameWorld()
{
    scene = new GameplayInterface();

    scene->setSceneRect(0,0,700,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(700,700);

    terrain = new QGraphicsEllipseItem(10,10,680,680);
    scene->addItem(terrain);


}
