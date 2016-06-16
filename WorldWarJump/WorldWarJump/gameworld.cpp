#include "gameworld.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "GameplayInterface.h"
#include "terrain.h"
#include "worldobject.h"
#include "physicscalc.h"
#include "battleunit.h"
#include <QDebug>
#include "gamesettings.h"

#include <stdlib.h>
#include <cmath>
#include "input.h"

#define M_PI 3.14159

GameWorld::GameWorld()
{
    gameWorldSize = settings->getGameWorldSize();
    setGameWorldSize(gameWorldSize);
    scene = new GameplayInterface();
    scene->setSceneRect(0,0,gameWorldSize,gameWorldSize);
    setScene(scene);

    setFixedSize(gameWorldSize,gameWorldSize);

    Terrain *terrain = new Terrain;
    scene->addItem(terrain);


    // Scrollbar disabling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Input-connection to World scene
    input = new Input();
    input->setRect(0,0,gameWorldSize,gameWorldSize);
    scene->addItem(input);

    addUnits();


    double e1[2]={300,300};
    double p1[2]={1,M_PI};
    double e2[2]={0};
    double p2[2]={0};

    PhysicsCalc* p= new PhysicsCalc();
    p->eulToPol(e1,p2,'p');
    p->polToEul(p1,e2,'v');

    qDebug() << p2[0] << p2[1];
    qDebug() << e2[0] << e2[1];
    p->eulToPol(e2,p1,'v');
    p->polToEul(p2,e1,'p');
    qDebug() << p1[0] << p1[1];
    qDebug() << e1[0] << e1[1];
}

int GameWorld::getGameWorldSize() const
{
    return gameWorldSize;
}

void GameWorld::setGameWorldSize(int value)
{
    gameWorldSize = value;
}

void GameWorld::pause()
{
    input->timer->stop();

}

void GameWorld::resume()
{
    input->timer->start(20);
}

void GameWorld::addUnits()
{
    int player1Units = settings->getPlayer1UnitCount();
    for(int i = 1; i <= player1Units; i++){
        BattleUnit *player1Unit = new BattleUnit(this,player1,Tank);
        player1Unit->setPos(gameWorldSize/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player1Unit);
    }
    int player2Unit = settings->getPlayer2UnitCount();
    for(int i = 1; i <= player2Unit; i++){
        BattleUnit *player2Unit = new BattleUnit(this,player2, Ship);
        player2Unit->setPos(gameWorldSize*2/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player2Unit);
    }
}

