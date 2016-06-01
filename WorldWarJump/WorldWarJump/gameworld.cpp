#include "gameworld.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "GameplayInterface.h"

GameWorld::GameWorld()
{
    setGameWorldSize(700);
    scene = new GameplayInterface();
    scene->setSceneRect(0,0,GameWorldSize,GameWorldSize);
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
    input->setRect(0,0,GameWorldSize,GameWorldSize);
    scene->addItem(input);
}

int GameWorld::getGameWorldSize() const
{
    return GameWorldSize;
}

void GameWorld::setGameWorldSize(int value)
{
    GameWorldSize = value;
}

void GameWorld::pause()
{
    input->timer->stop();

}

void GameWorld::resume()
{
    input->timer->start(20);
}

