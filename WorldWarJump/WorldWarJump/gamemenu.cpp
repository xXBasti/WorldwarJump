#include "gamemenu.h"
#include "worldobject.h"
#include "gameworld.h"
#include "gamesettings.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>
#include <QApplication>

#define M_PI 3.14159

GameMenu::GameMenu()
{    
    settings = new GameSettings;

    topMargin = 50;
    sideMargin = 50;
    buttonHeight = 75;
    buttonWidth = 75;
    unitHeight = 75;
    unitWidth = 75;

    setGameMenuSize(800);

    startScene = new QGraphicsScene;
    startSceneBackground = new QGraphicsPixmapItem;
    startSceneBackground->setPixmap(QPixmap(":/images/menubackground.png"));

    startButton = new QGraphicsPixmapItem;
    startButton->setPixmap(QPixmap(":/images/startbutton.png"));
    startButton->setPos(sideMargin,topMargin*2+200);

    settingsButton = new QGraphicsPixmapItem;
    settingsButton->setPixmap(QPixmap(":/images/settingsbutton.png"));
    settingsButton->setPos(sideMargin,topMargin*3+250);

    aboutButton = new QGraphicsPixmapItem;
    aboutButton->setPixmap(QPixmap(":/images/aboutbutton.png"));
    aboutButton->setPos(sideMargin,topMargin*4+300);

    exitButton = new QGraphicsPixmapItem;
    exitButton->setPixmap(QPixmap(":/images/exitbutton.png"));
    exitButton->setPos(sideMargin,topMargin*5+350);

    startScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
    setScene(startScene);
    setFixedSize(GameMenuSize,GameMenuSize);


    startScene->addItem(startSceneBackground);
    startScene->addItem(startButton);
    startScene->addItem(settingsButton);
    startScene->addItem(aboutButton);
    startScene->addItem(exitButton);


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
        if((item == this->startButton) && !(settings->getBeforeGameSceneAlreadyCreated()))                   // Open beforeGameScene.
        {
            beforeGameScene = new QGraphicsScene;
            beforeGameSceneBackground = new QGraphicsPixmapItem;
            beforeGameSceneBackground->setPixmap(QPixmap(":/images/menubackground.png"));

            addPlayer1UnitButton = new QGraphicsPixmapItem;
            addPlayer1UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer1UnitButton->setPos(sideMargin*2+unitWidth,topMargin*4);

            addPlayer2UnitButton = new QGraphicsPixmapItem;
            addPlayer2UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer2UnitButton->setPos(sideMargin*2+unitWidth,topMargin*5+buttonHeight);

            removePlayer1UnitButton = new QGraphicsPixmapItem;
            removePlayer1UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer1UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*4);

            removePlayer2UnitButton = new QGraphicsPixmapItem;
            removePlayer2UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer2UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*5+buttonHeight);

            changeStageButton = new QGraphicsPixmapItem;
            changeStageButton->setPixmap(QPixmap("ADD PATH"));
            changeStageButton->setPos(GameMenuSize-sideMargin-buttonWidth,topMargin*4);

            startBattleButton = new QGraphicsPixmapItem;
            startBattleButton->setPixmap(QPixmap(":/images/startbattlebutton.png"));
            startBattleButton->setPos(GameMenuSize-sideMargin-buttonWidth,GameMenuSize-topMargin-buttonHeight);

            player1UnitPicture = new QGraphicsPixmapItem;
            player1UnitPicture->setPixmap(QPixmap("ADD PATH"));
            player1UnitPicture->setPos(sideMargin,topMargin*4);

            player2UnitPicture = new QGraphicsPixmapItem;
            player2UnitPicture->setPixmap(QPixmap("ADD PATH"));
            player2UnitPicture->setPos(sideMargin,topMargin*5+unitHeight);

            titlePicture = new QGraphicsPixmapItem;
            titlePicture->setPixmap(QPixmap("ADD PATH"));
            titlePicture->setPos(sideMargin,topMargin);

            stagePicture = new QGraphicsPixmapItem;
            stagePicture->setPixmap(QPixmap("ADD PATH"));
            stagePicture->setPos(sideMargin*4+buttonWidth*2+unitWidth,topMargin*4);

            backButton = new QGraphicsPixmapItem;
            backButton->setPixmap(QPixmap(":/images/backbutton.png"));
            backButton->setPos(sideMargin,GameMenuSize-topMargin-buttonHeight);

            player1UnitCountPicture = new QGraphicsPixmapItem;
            player1UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
            player1UnitCountPicture->setPos(sideMargin*3+unitWidth+12.5,topMargin*4);

            player2UnitCountPicture = new QGraphicsPixmapItem;
            player2UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
            player2UnitCountPicture->setPos(sideMargin*3+unitWidth+12.5,topMargin*5+unitHeight);

            beforeGameScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(beforeGameScene);
            setFixedSize(GameMenuSize,GameMenuSize);

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
            beforeGameScene->addItem(backButton);
            beforeGameScene->addItem(player1UnitCountPicture);
            beforeGameScene->addItem(player2UnitCountPicture);

            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);\

            settings->setBeforeGameSceneAlreadyCreated(true);

        } else if((item == this->startButton) && (settings->getBeforeGameSceneAlreadyCreated()))
        {
            setScene(beforeGameScene);
        } else if(item == this->startBattleButton)                      //StartBattleButton Pressed, which means start the game.
        {
            GameWorld *gameScene = new GameWorld;
            this->setScene(gameScene->scene);

        } else if(item == this->addPlayer1UnitButton)                   // Add player1 unit.
        {
            player1UnitCount = settings->getPlayer1UnitCount();
            player1UnitCount++;
            settings->setPlayer1UnitCount(player1UnitCount);
            qDebug()<<player1UnitCount;
            switch(player1UnitCount)
            {
            case 2:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                //beforeGameScene->addItem(player1UnitCountPicture);
                break;
            case 3:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                //beforeGameScene->addItem(player1UnitCountPicture);
                break;
            case 4:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
                //beforeGameScene->addItem(player1UnitCountPicture);
                break;
            }

        } else if(item == this->addPlayer2UnitButton)                   // Add player2 unit.
        {
            player2UnitCount = settings->getPlayer2UnitCount();
            player2UnitCount++;
            settings->setPlayer2UnitCount(player2UnitCount);
            switch(player2UnitCount)
            {
            case 2:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
               // beforeGameScene->addItem(player2UnitCountPicture);
                break;
            case 3:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
               // beforeGameScene->addItem(player2UnitCountPicture);
                break;
            case 4:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
               // beforeGameScene->addItem(player2UnitCountPicture);
                break;
            }

        } else if(item == this->removePlayer1UnitButton)                // Remove player1 unit.
        {
            player1UnitCount = settings->getPlayer1UnitCount();
            if(player1UnitCount>1)
            {
                player1UnitCount--;
                settings->setPlayer1UnitCount(player1UnitCount);

            }

            switch(player1UnitCount)
            {
            case 1:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
              //  beforeGameScene->addItem(player1UnitCountPicture);
                break;
            case 2:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
               // beforeGameScene->addItem(player1UnitCountPicture);
                break;
            case 3:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                //beforeGameScene->addItem(player1UnitCountPicture);
                break;
            case 4:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
               // beforeGameScene->addItem(player1UnitCountPicture);
                break;
            }
            qDebug()<<player1UnitCount;


        } else if(item == this->removePlayer2UnitButton)                // Remove player2 unit.
        {
            player2UnitCount = settings->getPlayer2UnitCount();
            if(player2UnitCount>1)
            {
                player2UnitCount--;
                settings->setPlayer2UnitCount(player2UnitCount);

            }

            switch(player2UnitCount)
            {
            case 1:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
               // beforeGameScene->addItem(player2UnitCountPicture);
                break;
            case 2:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                //beforeGameScene->addItem(player2UnitCountPicture);
                break;
            case 3:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                //beforeGameScene->addItem(player2UnitCountPicture);
                break;
            case 4:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
               // beforeGameScene->addItem(player2UnitCountPicture);
                break;
            }

        } else if(item == this->changeStageButton)                      // Change game stage.
        {
            if(whichStage == 1) whichStage++;
            if(whichStage == 2) whichStage--;

        } else if(item == this->backButton)                             // Go back to main menu.
        {
            setScene(startScene);
            setFixedSize(GameMenuSize,GameMenuSize);
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        } else if(item == this->settingsButton)                         // Open settings.
        {
            settingsScene = new QGraphicsScene;

        } else if(item == this->aboutButton)                            // Open about.
        {

        } else if (item == this->exitButton)                            // Exit the game.
        {
            QApplication::quit();
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

