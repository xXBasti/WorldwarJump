#include "gameworld.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "GameplayInterface.h"
#include "worldobject.h"
#include "physicscalc.h"
#include "battleunit.h"
#include <QDebug>
#include "gamesettings.h"
#include <stdlib.h>
#include <cmath>
#include "input.h"
#include "terrain.h"

#define M_PI 3.14159

GameWorld::GameWorld()
{
    setGameWorldSize(settings->getGameWorldSize());
    setFixedSize(gameWorldSize,gameWorldSize);

    scene = new GameplayInterface();
    setScene(scene);

    connect(scene->physicsCalulator,SIGNAL(playeronewins()),this,SLOT(playeronewins()));
    connect(scene->physicsCalulator,SIGNAL(playertwowins()),this,SLOT(playertwowins()));

    // Input-connection to World scene
    input = new Input();
    scene->addItem(input);

    // terrain, background and level switch timer

    background = new QGraphicsPixmapItem;
    background->setPixmap(QPixmap(":/images/weltallBackground.png"));
    scene->addItem(background);

    terrain = new Terrain;
    scene->addItem(terrain);

    levelSwitchTimer = new QTimer();
    levelSwitchTimer->start(settings->getSecondsToChangeLevel()*1000);
    connect(levelSwitchTimer, SIGNAL(timeout()), this, SLOT(changeLevel()));

    addUnits();

    // Scrollbar disabling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //What are the next lines?
//    double e1[2]={300,300};
//    double p1[2]={1,M_PI};
//    double e2[2]={0};
//    double p2[2]={0};

//    PhysicsCalc* p= new PhysicsCalc();
//    p->eulToPol(e1,p2,'p');
//    p->polToEul(p1,e2,'v');

//    qDebug() << p2[0] << p2[1];
//    qDebug() << e2[0] << e2[1];
//    p->eulToPol(e2,p1,'v');
//    p->polToEul(p2,e1,'p');
//    qDebug() << p1[0] << p1[1];
//    qDebug() << e1[0] << e1[1];
}

void GameWorld::setGameWorldSize(int value)
{
    gameWorldSize = value;
}

void GameWorld::pause()
{
    input->timer->stop();
    levelSwitchTimer->stop();
}

void GameWorld::resume()
{
    input->timer->start(20);
    levelSwitchTimer->start(settings->getSecondsToChangeLevel()*1000);
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

void GameWorld::changeLevel()
{
    int stage = settings->getWhichStage();
    /*
    switch(stage){
    case 0:
        levelSwitchTimer->start(settings->getSecondsToChangeLevel()*1000);
        background->setPixmap(QPixmap(":/images/pics/bomb.jpg"));
        terrain->setPixmap(QPixmap(":/images/terrainbackground.png"));
        scene->physicsCalulator->gravity = settings->getGravity();
        break;
    case 1:
        levelSwitchTimer->start(settings->getSecondsToChangeLevel()*1000/2);
        background->setPixmap(QPixmap(":/images/pics/space.jpg"));
        terrain->setPixmap(QPixmap(":/images/terrainbackground.png"));
        scene->physicsCalulator->gravity = -settings->getGravity()/2;
        break;
    case 2:
        levelSwitchTimer->start(settings->getSecondsToChangeLevel()*1000);
        background->setPixmap(QPixmap(":/images/background.png"));
        terrain->setPixmap(QPixmap(":/images/terrainbackground.png"));
        scene->physicsCalulator->gravity = settings->getGravity();
        break;
    default:
        qDebug() << "stage number out of boundaries";
    }
    settings->setWhichStage((stage + 1)%3);
    qDebug() << "Level changed!";
    */
}

void GameWorld::playeronewins()
{
    emit this->playeronewinsSignal();
}

void GameWorld::playertwowins()
{
    emit this->playertwowinsSignal();
}



