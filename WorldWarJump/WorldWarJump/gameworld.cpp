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
    GameSettings * settings;
    GameWorldSize = settings->getGameWorldSize();
    setGameWorldSize(GameWorldSize);
    scene = new GameplayInterface();
    scene->setSceneRect(0,0,GameWorldSize,GameWorldSize);
    setScene(scene);

    setFixedSize(GameWorldSize,GameWorldSize);

    Terrain *terrain = new Terrain;
    scene->addItem(terrain);


    // Scrollbar disabling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Input-connection to World scene
    input = new Input();
    input->setRect(0,0,GameWorldSize,GameWorldSize);
    scene->addItem(input);

    BattleUnit *player1Unit2 = new BattleUnit(this,player1,Tank);
    player1Unit2->setPos(GameWorldSize/2,GameWorldSize/3);
    scene->addItem(player1Unit2);

    BattleUnit *player1Unit1 = new BattleUnit(this,player1,Tank);
    player1Unit1->setPos(GameWorldSize/2,GameWorldSize/2);
    scene->addItem(player1Unit1);

    BattleUnit *player2Unit2 = new BattleUnit(this,player2,Ship);
    player2Unit2->setPos(GameWorldSize/3,GameWorldSize/2);
    scene->addItem(player2Unit2);

    BattleUnit *player2Unit1 = new BattleUnit(this,player2,Ship);
    player2Unit1->setPos(GameWorldSize/3,GameWorldSize/3);
    scene->addItem(player2Unit1);

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

