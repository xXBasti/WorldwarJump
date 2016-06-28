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
#include <QProgressBar>
#include "input.h"
#include "terrain.h"
#include <QLabel>
#include "background.h"
#include <QTimer>

#define M_PI 3.14159

GameWorld::GameWorld(SoundPlayer *soundplayer)
{
    soundpointer = soundplayer;
    setGameWorldSize(settings->getGameWorldSize());
    setFixedSize(gameWorldSize,gameWorldSize);

    scene = new GameplayInterface(soundplayer);
    setScene(scene);

    connect(scene->physicsCalulator,SIGNAL(playeronewins()),this,SLOT(playeronewins()));
    connect(scene->physicsCalulator,SIGNAL(playertwowins()),this,SLOT(playertwowins()));
    connect(scene->physicsCalulator,SIGNAL(meeleDmg()),this,SLOT(displayMeele()));
    // Input-connection to World scene
    input = new Input();
    scene->addItem(input);

    // terrain, background and level switch timer
    backGroundRotationTimer = new QTimer();
    connect(backGroundRotationTimer, SIGNAL(timeout()), this, SLOT(rotateBackground()));

    background = new BackGround(settings,backGroundRotationTimer);
    scene->addItem(background);

    terrain = new Terrain(settings,scene);
    scene->addItem(terrain);

    QLabel* lOne=new QLabel();
    lOne->setGeometry(5,5,80,15);
    lOne->setText("Player Red");
    //lOne->setAttribute(Qt::WA_TranslucentBackground); could be nice transparent?!
    scene->addWidget(lOne);
    QLabel* lTwo=new QLabel();
    lTwo->setGeometry(715,5,80,15);
    lTwo->setText("Player Blue");
    scene->addWidget(lTwo);
    addUnits();

    display=new QLabel();
    display->setGeometry(700,700,100,50);
    display->setAttribute(Qt::WA_TranslucentBackground);
    display->setStyleSheet("QLabel {color: red; font-weight: bold}");
    display->setText("MEELE");
    QFont font =display->font();
    font.setPointSize(20);
    display->setFont(font);
    scene->addWidget(display);
    display->setVisible(false);
    meeleTimer= new QTimer();
    connect(meeleTimer,SIGNAL(timeout()),this,SLOT(hideMeele()));
    // Scrollbar disabling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void GameWorld::setGameWorldSize(int value)
{
    gameWorldSize = value;
}

void GameWorld::pause()
{
    input->refreshRateTimer->stop();
}

void GameWorld::resume()
{
    input->refreshRateTimer->start(20);
}

void GameWorld::addUnits()
{
    int playerRedTanks = settings->getPlayerRedTankCount();
    int playerRedShips = settings->getPlayerRedShipCount();
    int playerBlueTanks = settings->getPlayerBlueTankCount();
    int playerBlueShips = settings->getPlayerBlueShipCount();
    int i;

    for(i = 1; (playerRedTanks!=0) && (i <= playerRedTanks); i++){
        BattleUnit *player1Unit = new BattleUnit(this,player1,soundpointer, Tank);
        player1Unit->setPos(gameWorldSize/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player1Unit);
        QProgressBar* poh= new QProgressBar();
        scene->addWidget(poh);
        poh->setMaximumWidth(80);
        poh->setMaximumHeight(10);
        poh->setValue(100);
        poh->setGeometry(5,25+(i-1)*20,100,15);
        poh->setMaximum(100);
        poh->setTextVisible(false);
        poh->setVisible(true);
        connect(player1Unit,SIGNAL(sendHealth(int)),poh,SLOT(setValue(int)));
    }

    for((playerRedShips!=0) && (i = playerRedTanks+1); i <= playerRedTanks+playerRedShips; i++){
        BattleUnit *player1Unit = new BattleUnit(this,player1,soundpointer, Ship);
        player1Unit->setPos(gameWorldSize/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player1Unit);
        QProgressBar* poh= new QProgressBar();
        scene->addWidget(poh);
        poh->setMaximumWidth(80);
        poh->setMaximumHeight(10);
        poh->setValue(100);
        poh->setGeometry(5,25+(i-1)*20,100,15);
        poh->setMaximum(100);
        poh->setTextVisible(false);
        poh->setVisible(true);
        connect(player1Unit,SIGNAL(sendHealth(int)),poh,SLOT(setValue(int)));
    }

    for((playerBlueShips!=0) && (i = 1); i <= playerBlueShips; i++){
        BattleUnit *player2Unit = new BattleUnit(this,player2,soundpointer, Ship);
        player2Unit->setPos(gameWorldSize*2/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player2Unit);
        QProgressBar* pth= new QProgressBar();
        scene->addWidget(pth);
        pth->setMaximumWidth(80);
        pth->setMaximumHeight(10);
        pth->setMaximum(100);
        pth->setValue(100);
        pth->setGeometry(715,25+(i-1)*15,80,10);
        pth->setTextVisible(false);
        pth->setVisible(true);
        connect(player2Unit,SIGNAL(sendHealth(int)),pth,SLOT(setValue(int)));
    }

    for((playerBlueTanks!=0) && (i = playerBlueShips+1); i <= playerBlueShips+playerBlueTanks; i++){
        BattleUnit *player2Unit = new BattleUnit(this,player2,soundpointer, Tank);
        player2Unit->setPos(gameWorldSize*2/3,(1+(double)i/2)*gameWorldSize/4);
        scene->addItem(player2Unit);
        QProgressBar* pth= new QProgressBar();
        scene->addWidget(pth);
        pth->setMaximumWidth(80);
        pth->setMaximumHeight(10);
        pth->setMaximum(100);
        pth->setValue(100);
        pth->setGeometry(715,25+(i-1)*15,80,10);
        pth->setTextVisible(false);
        pth->setVisible(true);
        connect(player2Unit,SIGNAL(sendHealth(int)),pth,SLOT(setValue(int)));
    }

}

void GameWorld::playeronewins()
{
    emit this->playeronewinsSignal();
}

void GameWorld::playertwowins()
{
    emit this->playertwowinsSignal();
}


void GameWorld::rotateBackground()
{
    //qDebug() << background->rotation();
    background->setRotation(background->rotation()+0.2);
}

void GameWorld::displayMeele(){
    display->setVisible(true);
    meeleTimer->start(3000);
}

void GameWorld::hideMeele(){
    display->setVisible(false);
    meeleTimer->stop();
}


GameWorld::~GameWorld()
{
    //delete scene;
    //delete input;
    //delete backGroundRotationTimer;
    //delete background;
    //delete terrain;
    qDebug()<<"and I'm out...";

}
