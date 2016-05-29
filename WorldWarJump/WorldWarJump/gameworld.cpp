#include "gameworld.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "GameplayInterface.h"

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

    // Scrollbar disabling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Input-connection to World scene
    input = new Input();

    scene->addItem(input);
}
