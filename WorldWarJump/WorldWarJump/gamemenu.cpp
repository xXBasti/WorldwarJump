#include "gamemenu.h"
#include "worldobject.h"
#include "gameworld.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>

//#define M_PI 3.14159

GameMenu::GameMenu()
{    
    topMargin = 50;
    sideMargin = 50;

    player1UnitCount = 1;
    player2UnitCount = 1;
    whichStage = 1;

    setGameMenuSize(700);

    startScene = new QGraphicsScene;
    startSceneBackground = new QGraphicsPixmapItem;
    startSceneBackground->setPixmap(QPixmap(":/images/menubackground.png"));

    startButton = new QGraphicsPixmapItem;
    startButton->setPixmap(QPixmap(":/images/startbutton.png"));
    startButton->setPos(100,300);
    settingsButton = new QGraphicsPixmapItem;
    exitButton = new QGraphicsPixmapItem;

    startScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
    setScene(startScene);
    setFixedSize(700,700);


    startScene->addItem(startSceneBackground);
    startScene->addItem(startButton);


    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    w->setCentralWidget(this);
    w->show();



}

int GameMenu::getGameMenuSize() const
{
    return GameMenuSize;
}

void GameMenu::setGameMenuSize(int value)
{
    GameMenuSize = value;
}


void GameMenu::mousePressEvent(QMouseEvent *event)
{
    if(QGraphicsItem *item = itemAt(event->pos()))
    {
        if(item == this->startButton)
        {
            beforeGameScene = new QGraphicsScene;
            beforeGameSceneBackground = new QGraphicsPixmapItem;
            beforeGameSceneBackground->setPixmap(QPixmap(":/images/menubackground.png"));

            addPlayer1UnitButton = new QGraphicsPixmapItem;
            addPlayer1UnitButton->setPixmap(QPixmap("ADD PATH"));
            addPlayer1UnitButton->setPos(sideMargin*2+50,topMargin*2+50);

            addPlayer2UnitButton = new QGraphicsPixmapItem;
            addPlayer2UnitButton->setPixmap(QPixmap("ADD PATH"));
            addPlayer2UnitButton->setPos(sideMargin*2+50,topMargin*3+100);

            removePlayer1UnitButton = new QGraphicsPixmapItem;
            removePlayer1UnitButton->setPixmap(QPixmap("ADD PATH"));
            removePlayer1UnitButton->setPos(sideMargin*3+100,topMargin*2+50);

            removePlayer2UnitButton = new QGraphicsPixmapItem;
            removePlayer2UnitButton->setPixmap(QPixmap("ADD PATH"));
            removePlayer2UnitButton->setPos(sideMargin*3+100,topMargin*3+100);

            changeStageButton = new QGraphicsPixmapItem;
            changeStageButton->setPixmap(QPixmap("ADD PATH"));
            changeStageButton->setPos(GameMenuSize-sideMargin,topMargin*2+50);

            startBattleButton = new QGraphicsPixmapItem;
            startBattleButton->setPixmap(QPixmap(":/images/startbutton.png"));
            startBattleButton->setPos(GameMenuSize-sideMargin,GameMenuSize-topMargin);

            player1UnitPicture = new QGraphicsPixmapItem;
            player1UnitPicture->setPixmap(QPixmap("ADD PATH"));
            player1UnitPicture->setPos(sideMargin,topMargin*2+50);

            player2UnitPicture = new QGraphicsPixmapItem;
            player2UnitPicture->setPixmap(QPixmap("ADD PATH"));
            player2UnitPicture->setPos(sideMargin,topMargin*3+100);

            titlePicture = new QGraphicsPixmapItem;
            titlePicture->setPixmap(QPixmap("ADD PATH"));
            titlePicture->setPos(sideMargin,topMargin);

            stagePicture = new QGraphicsPixmapItem;
            stagePicture->setPixmap(QPixmap("ADD PATH"));
            stagePicture->setPos(sideMargin*4+150,topMargin*2+50);

            beforeGameScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(beforeGameScene);
            setFixedSize(700,700);

            beforeGameScene->addItem(beforeGameSceneBackground);
            beforeGameScene->addItem(addPlayer1UnitButton);
            beforeGameScene->addItem(addPlayer2UnitButton);
            beforeGameScene->addItem(removePlayer1UnitButton);
            beforeGameScene->addItem(removePlayer2UnitButton);
            beforeGameScene->addItem(changeStageButton);
            beforeGameScene->addItem(startBattleButton);
            beforeGameScene->addItem(stagePicture);
            beforeGameScene->addItem(titlePicture);
            beforeGameScene->addItem(player1UnitPicture);
            beforeGameScene->addItem(player2UnitPicture);

            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        } else if(item == this->startBattleButton)
        {
            GameWorld *gameScene = new GameWorld;
            w->setCentralWidget(gameScene);
            w->show();

        } else if(item == this->addPlayer1UnitButton)
        {
            player1UnitCount++;
            qDebug()<<player1UnitCount;
        } else if(item == this->addPlayer2UnitButton)
        {
            player2UnitCount++;
        } else if(item == this->removePlayer1UnitButton)
        {
            if(player1UnitCount>1) player1UnitCount--;
        } else if(item == this->removePlayer2UnitButton)
        {
            if(player2UnitCount>1) player2UnitCount--;
        } else if(item == this->changeStageButton)
        {
            if(whichStage == 1) whichStage++;
            if(whichStage == 2) whichStage--;
        }
    }
}

int GameMenu::getPlayer1UnitCount() const
{
    return player1UnitCount;
}

int GameMenu::getPlayer2UnitCount() const
{
    return player2UnitCount;
}

int GameMenu::getWhichStage() const
{
    return whichStage;
}

