#include "gameworld.h"
#include <QGraphicsScene>
#include "GameplayInterface.h"

GameWorld::GameWorld()
{
    scene = new GameplayInterface();

    setScene(scene);
    setFixedSize(1024,768);

}
