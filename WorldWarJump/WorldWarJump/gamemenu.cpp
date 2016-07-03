#include "gamemenu.h"
#include "worldobject.h"
#include "gameworld.h"
#include "gamesettings.h"
#include "mainwindow.h"
#include "physicscalc.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>
#include <QApplication>
#include <QMediaPlayer>

#define M_PI 3.14159

GameMenu::GameMenu(SoundPlayer *soundplayer)
{    
    settings = new GameSettings;
    gamealreadyexist = false;

    soundpointer = soundplayer;
    soundpointer->playMenuBGM();

    topMargin = 50;
    sideMargin = 50;
    buttonHeight = 30;
    buttonWidth = 30;
    unitHeight = 30;
    unitWidth = 100;

    setGameMenuSize(800);

    startScene = new QGraphicsScene;
    startSceneBackground = new QGraphicsPixmapItem;
    startSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

    startButton = new QGraphicsPixmapItem;
    startButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/PlayButton.png"));
    startButton->setPos(sideMargin,topMargin*2+200);

    settingsButton = new QGraphicsPixmapItem;
    settingsButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/SettingsButton.png"));
    settingsButton->setPos(sideMargin,topMargin*3+250);

    aboutButton = new QGraphicsPixmapItem;
    aboutButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/AboutButton.png"));
    aboutButton->setPos(sideMargin,topMargin*4+300);

    exitButton = new QGraphicsPixmapItem;
    exitButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/ExitButton.png"));
    exitButton->setPos(sideMargin,topMargin*5+350);

    backButton = new QGraphicsPixmapItem;
    backButton->setPixmap(QPixmap(":/images/backbutton.png"));
    backButton->setPos(sideMargin,GameMenuSize-topMargin-buttonHeight);
    backButton->setZValue(1);

    thumbnail = new QGraphicsPixmapItem;       //space is stage 1, earth is stage 2
    thumbnail->setPos(sideMargin*5+unitWidth+buttonWidth*3+30,topMargin*5-50);
    thumbnail->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/spaceThumbnail.png"));
    thumbnail->setZValue(1);

    yesorno = new QGraphicsPixmapItem;
    yesorno->setPixmap(QPixmap(":/images/pics/MenusAndButtons/yes.png"));
    yesorno->setZValue(1);
    yesorno->setPos(sideMargin*5+unitWidth+buttonWidth*3+30,topMargin*8+180);

    muteBGMButton = new QGraphicsPixmapItem;
    switch(settings->getBGMMuted())
    {
    case true:
        break;
        muteBGMButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/unmuteBGM.png"));
    case false:
        muteBGMButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/muteBGMnew.png"));
        break;
    }
    muteBGMButton->setPos(GameMenuSize-sideMargin*3,topMargin*4);
    muteBGMButton->setZValue(1);

    muteSEButton = new QGraphicsPixmapItem;
    switch(settings->getSEMuted())
    {
    case true:
        muteSEButton->setPixmap(QPixmap("::/images/pics/MenusAndButtons/unmuteSE.png"));
        break;
    case false:
        muteSEButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/muteSEnew.png"));
        break;
    }
    muteSEButton->setPos(GameMenuSize-sideMargin*3,topMargin*5+unitHeight*2);
    muteSEButton->setZValue(1);

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
/**
 * @brief GameMenu::getGameMenuSize() returns the set resolution of the game menu.
 * @return the set resolution of the menu
 */

int GameMenu::getGameMenuSize() const
{
    return GameMenuSize;
}

/** @brief GameMenu::setGameMenuSize(int value) sets the resolution of the menu
 * @param the wished resolutio
 */

void GameMenu::setGameMenuSize(int value)
{
    GameMenuSize = value;
}

/** @brief GameMenu::mousePressEvent(QMouseEvent *event) secures the main functionality of the menu. It detects mouse clicks and compares the QGraphicsItem
 * on which the mouse is currently positioned with buttons, which are inherited from QGraphicsPixmapItem, then acts correspondingly.
 */


void GameMenu::mousePressEvent(QMouseEvent *event)
{
    if(QGraphicsItem *item = itemAt(event->pos()))
    {
        if((item == this->startButton) && !(settings->getBeforeGameSceneAlreadyCreated()))                   // Open beforeGameScene.
        {
            beforeGameScene = new QGraphicsScene;
            beforeGameSceneBackground = new QGraphicsPixmapItem;
            beforeGameSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

            addPlayer1UnitButton = new QGraphicsPixmapItem;
            addPlayer1UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer1UnitButton->setPos(sideMargin*2+unitWidth,topMargin*4);
            addPlayer1UnitButton->setZValue(1);

            addPlayer2UnitButton = new QGraphicsPixmapItem;
            addPlayer2UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer2UnitButton->setPos(sideMargin*2+unitWidth,topMargin*5+buttonHeight);
            addPlayer2UnitButton->setZValue(1);

            addRedShipButton = new QGraphicsPixmapItem;
            addRedShipButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addRedShipButton->setZValue(1);
            addRedShipButton->setPos(sideMargin*2+unitWidth,topMargin*8+buttonHeight*4);

            addRedTankButton = new QGraphicsPixmapItem;
            addRedTankButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addRedTankButton->setZValue(1);
            addRedTankButton->setPos(sideMargin*2+unitWidth,topMargin*7+buttonHeight*3);

            addBlueShipButton = new QGraphicsPixmapItem;
            addBlueShipButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addBlueShipButton->setZValue(1);
            addBlueShipButton->setPos(sideMargin*2+unitWidth,topMargin*6+buttonHeight);

            addBlueTankButton = new QGraphicsPixmapItem;
            addBlueTankButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addBlueTankButton->setZValue(1);
            addBlueTankButton->setPos(sideMargin*2+unitWidth,topMargin*5);

            removeRedShipButton = new QGraphicsPixmapItem;
            removeRedShipButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removeRedShipButton->setZValue(1);
            removeRedShipButton->setPos(unitWidth+sideMargin*4+buttonWidth*2,topMargin*8+buttonHeight*4);

            removeRedTankButton = new QGraphicsPixmapItem;
            removeRedTankButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removeRedTankButton->setZValue(1);
            removeRedTankButton->setPos(unitWidth+sideMargin*4+buttonWidth*2,topMargin*7+buttonHeight*3);

            removeBlueShipButton = new QGraphicsPixmapItem;
            removeBlueShipButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removeBlueShipButton->setZValue(1);
            removeBlueShipButton->setPos(unitWidth+sideMargin*4+buttonWidth*2,topMargin*6+buttonHeight);

            removeBlueTankButton = new QGraphicsPixmapItem;
            removeBlueTankButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removeBlueTankButton->setZValue(1);
            removeBlueTankButton->setPos(unitWidth+sideMargin*4+buttonWidth*2,topMargin*5);

            removePlayer1UnitButton = new QGraphicsPixmapItem;
            removePlayer1UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer1UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*4);
            removePlayer1UnitButton->setZValue(1);

            removePlayer2UnitButton = new QGraphicsPixmapItem;
            removePlayer2UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer2UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*5+buttonHeight);
            removePlayer2UnitButton->setZValue(1);

            changeStageButton = new QGraphicsPixmapItem;
            changeStageButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/changestagebutton.png"));
            changeStageButton->setPos(sideMargin*5+unitWidth+buttonWidth*3+30,topMargin*6+120);
            changeStageButton->setZValue(1);

            startBattleButton = new QGraphicsPixmapItem;
            startBattleButton->setPixmap(QPixmap(":/images/startbattlebutton.png"));
            startBattleButton->setPos(GameMenuSize-sideMargin-buttonWidth,GameMenuSize-topMargin-buttonHeight);
            startBattleButton->setZValue(1);

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

            player1UnitCountPicture = new QGraphicsPixmapItem;
            player1UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
            player1UnitCountPicture->setPos(sideMargin*3+unitWidth+12.5,topMargin*4);

            player2UnitCountPicture = new QGraphicsPixmapItem;
            player2UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
            player2UnitCountPicture->setPos(sideMargin*3+unitWidth+12.5,topMargin*5+unitHeight);

            playerRedShipCountPicture = new QGraphicsPixmapItem;
            playerRedShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
            playerRedShipCountPicture->setPos(unitWidth+sideMargin*3+buttonWidth,topMargin*8+unitHeight*4);

            playerRedTankCountPicture = new QGraphicsPixmapItem;
            playerRedTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
            playerRedTankCountPicture->setPos(unitWidth+sideMargin*3+buttonWidth,topMargin*7+unitHeight*3);

            playerBlueShipCountPicture = new QGraphicsPixmapItem;
            playerBlueShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
            playerBlueShipCountPicture->setPos(unitWidth+sideMargin*3+buttonWidth,topMargin*6+unitHeight);

            playerBlueTankCountPicture = new QGraphicsPixmapItem;
            playerBlueTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
            playerBlueTankCountPicture->setPos(unitWidth+sideMargin*3+buttonWidth,topMargin*5);

            redShipPicture = new QGraphicsPixmapItem;
            redShipPicture->setPixmap(QPixmap(":/images/redship100.png"));
            redShipPicture->setPos(sideMargin,topMargin*8+unitHeight*4);

            redTankPicture = new QGraphicsPixmapItem;
            redTankPicture->setPixmap(QPixmap(":/images/redtank100.png"));
            redTankPicture->setPos(sideMargin,topMargin*7+unitHeight*3);

            blueShipPicture = new QGraphicsPixmapItem;
            blueShipPicture->setPixmap(QPixmap(":/images/blueship100.png"));
            blueShipPicture->setPos(sideMargin,topMargin*6+unitHeight);

            blueTankPicture = new QGraphicsPixmapItem;
            blueTankPicture->setPixmap(QPixmap(":/images/bluetank100.png"));
            blueTankPicture->setPos(sideMargin,topMargin*5);

            friendlyFireButton = new QGraphicsPixmapItem;
            friendlyFireButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/friendlyfire.png"));
            friendlyFireButton->setPos(sideMargin*5+unitWidth+buttonWidth*3+30,topMargin*7+150);
            friendlyFireButton->setZValue(1);


            beforeGameScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(beforeGameScene);
            setFixedSize(GameMenuSize,GameMenuSize);

            beforeGameScene->addItem(beforeGameSceneBackground);
            beforeGameScene->addItem(changeStageButton);
            beforeGameScene->addItem(startBattleButton);
            beforeGameScene->addItem(stagePicture);
            beforeGameScene->addItem(titlePicture);
            beforeGameScene->addItem(backButton);

            beforeGameScene->addItem(addRedShipButton);
            beforeGameScene->addItem(addRedTankButton);
            beforeGameScene->addItem(addBlueShipButton);
            beforeGameScene->addItem(addBlueTankButton);
            beforeGameScene->addItem(removeRedShipButton);
            beforeGameScene->addItem(removeRedTankButton);
            beforeGameScene->addItem(removeBlueShipButton);
            beforeGameScene->addItem(removeBlueTankButton);
            beforeGameScene->addItem(playerRedShipCountPicture);
            beforeGameScene->addItem(playerRedTankCountPicture);
            beforeGameScene->addItem(playerBlueShipCountPicture);
            beforeGameScene->addItem(playerBlueTankCountPicture);
            beforeGameScene->addItem(redShipPicture);
            beforeGameScene->addItem(redTankPicture);
            beforeGameScene->addItem(blueShipPicture);
            beforeGameScene->addItem(blueTankPicture);
            beforeGameScene->addItem(thumbnail);
            beforeGameScene->addItem(friendlyFireButton);
            beforeGameScene->addItem(yesorno);

            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            settings->setBeforeGameSceneAlreadyCreated(true);

        } else if((item == this->startButton) && (settings->getBeforeGameSceneAlreadyCreated()))
        {
            settings->resetUnitCount();
            setNumberPictureOnPixmap(settings->getPlayerBlueShipCount(), playerBlueShipCountPicture);
            setNumberPictureOnPixmap(settings->getPlayerBlueTankCount(), playerBlueTankCountPicture);
            setNumberPictureOnPixmap(settings->getPlayerRedShipCount(), playerRedShipCountPicture);
            setNumberPictureOnPixmap(settings->getPlayerRedTankCount(), playerRedTankCountPicture);
            beforeGameScene->addItem(backButton);
            setScene(beforeGameScene);

        } else if(item == this->startBattleButton)                      //StartBattleButton Pressed, which means start the game.
        {
            gamealreadyexist = true;
            GameWorld *gameScene = new GameWorld(soundpointer);
            reference = gameScene;
            connect(gameScene,SIGNAL(playeronewinsSignal()),this,SLOT(playeronewon()));
            connect(gameScene,SIGNAL(playertwowinsSignal()),this,SLOT(playertwowon()));

            this->setScene(gameScene->scene);
            gameScene->scene->addItem(backButton);
            soundpointer->playGameBGM();



        } else if(item == this->addPlayer1UnitButton)                   // Add player1 unit (redundant).
        {
            player1UnitCount = settings->getPlayer1UnitCount();
            player1UnitCount++;
            settings->setPlayer1UnitCount(player1UnitCount);
            switch(player1UnitCount)
            {
            case 2:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            }

        } else if(item == this->addRedShipButton)                   // Add ship for red player.
        {
            playerRedShipCount = settings->getPlayerRedShipCount();
            if(playerRedShipCount<2) playerRedShipCount++;
            settings->setPlayerRedShipCount(playerRedShipCount);
            switch(playerRedShipCount)
            {
            case 2:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 0:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            case 1:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            }
         } else if(item == this->addRedTankButton)              // Add tank for red player.
        {
            playerRedTankCount = settings->getPlayerRedTankCount();
            if(playerRedTankCount<2) playerRedTankCount++;
            settings->setPlayerRedTankCount(playerRedTankCount);
            switch(playerRedTankCount)
            {
            case 2:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 1:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 0:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->addBlueShipButton)              // Add ship for blue player.
        {
            playerBlueShipCount = settings->getPlayerBlueShipCount();
            if(playerBlueShipCount<2) playerBlueShipCount++;
            settings->setPlayerBlueShipCount(playerBlueShipCount);
            switch(playerBlueShipCount)
            {
            case 2:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 1:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 0:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->addBlueTankButton)              // Add tank for blue player.
        {
            playerBlueTankCount = settings->getPlayerBlueTankCount();
            if(playerBlueTankCount<2)playerBlueTankCount++;
            settings->setPlayerBlueTankCount(playerBlueTankCount);
            switch(playerBlueTankCount)
            {
            case 2:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 1:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 0:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }

        } else if(item == this->addPlayer2UnitButton)                   // Add player2 unit (redundant).
        {
            player2UnitCount = settings->getPlayer2UnitCount();
            player2UnitCount++;
            settings->setPlayer2UnitCount(player2UnitCount);
            switch(player2UnitCount)
            {
            case 2:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            }

        } else if(item == this->removePlayer1UnitButton)                // Remove player1 unit (redundant).
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
                break;
            case 2:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                player1UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            }

        } else if(item == this->removePlayer2UnitButton)                // Remove player2 unit (redundant).
        {
            player2UnitCount = settings->getPlayer2UnitCount();
            if(player2UnitCount>0)
            {
                player2UnitCount--;
                settings->setPlayer2UnitCount(player2UnitCount);

            }

            switch(player2UnitCount)
            {
            case 1:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 2:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                player2UnitCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            }
        } else if(item == this->removeRedShipButton)                    // Remove one ship from red player.
        {
            playerRedShipCount = settings->getPlayerRedShipCount();
            if(playerRedShipCount>0)
            {
                playerRedShipCount--;
                settings->setPlayerRedShipCount(playerRedShipCount);
            }
            switch(playerRedShipCount)
            {
            case 1:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 2:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 0:
                playerRedShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->removeRedTankButton)                    // Remove one tank from red player.
        {
            playerRedTankCount = settings->getPlayerRedTankCount();
            if(playerRedTankCount>0)
            {
                playerRedTankCount--;
                settings->setPlayerRedTankCount(playerRedTankCount);
            }
            switch(playerRedTankCount)
            {
            case 1:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 2:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 0:
                playerRedTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->removeBlueShipButton)                   // Remove one ship from blue player.
        {
            playerBlueShipCount = settings->getPlayerBlueShipCount();
            if(playerBlueShipCount>0)
            {
                playerBlueShipCount--;
                settings->setPlayerBlueShipCount(playerBlueShipCount);
            }
            switch(playerBlueShipCount)
            {
            case 1:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 2:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 0:
                playerBlueShipCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->removeBlueTankButton)                   // Remove one tank from blue player.
        {
            playerBlueTankCount = settings->getPlayerBlueTankCount();
            if(playerBlueTankCount>0)
            {
                playerBlueTankCount--;
                settings->setPlayerBlueTankCount(playerBlueTankCount);
            }
            switch(playerBlueTankCount)
            {
            case 1:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/1.png"));
                break;
            case 2:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/2.png"));
                break;
            case 3:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/3.png"));
                break;
            case 4:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/4.png"));
                break;
            case 0:
                playerBlueTankCountPicture->setPixmap(QPixmap(":/images/pics/0.png"));
                break;
            }
        } else if(item == this->changeStageButton)                      // Change game stage.
        {
            whichStage = settings->getWhichStage();

            if(whichStage == 1)
            {
                whichStage++;
                thumbnail->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/earthThumbnail.png"));
                settings->setWhichStage(whichStage);
                return;

            } else
            if(whichStage == 2)
            {
                whichStage--;
                thumbnail->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/spaceThumbnail.png"));
                settings->setWhichStage(whichStage);
                return;
            }


        } else if(item == this->backButton)                             // Go back to main menu.
        {
            setScene(startScene);
            if(gamealreadyexist)
            {
                delete reference;
                gamealreadyexist = false;
                soundpointer->playMenuBGM();
            }

        } else if((item == this->settingsButton)&&!(settings->getSettingsSceneAlreadyCreated()))                         // Open settings.
        {
            settingsScene = new QGraphicsScene;
            settingsBackground = new QGraphicsPixmapItem;
            settingsBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

            BGMslider = new QSlider;
            BGMslider->setOrientation(Qt::Horizontal);
            BGMslider->setRange(0,100);
            BGMslider->setGeometry(sideMargin*3+100,topMargin*4,300,75);
            SEslider = new QSlider;
            SEslider->setOrientation(Qt::Horizontal);
            SEslider->setRange(0,100);
            SEslider->setGeometry(sideMargin*3+100,topMargin*5+unitHeight*2,300,75);

            BGMslider->setSliderPosition(settings->getBGMvolume());
            SEslider->setSliderPosition(settings->getSEvolume());

            bgmVolume = new QGraphicsPixmapItem;
            bgmVolume->setPixmap(QPixmap(":/images/pics/MenusAndButtons/bgmvolume.png"));
            bgmVolume->setZValue(1);
            bgmVolume->setPos(sideMargin*2,topMargin*4);

            seVolume = new QGraphicsPixmapItem;
            seVolume->setPixmap(QPixmap(":/images/pics/MenusAndButtons/sevolume.png"));
            seVolume->setZValue(1);
            seVolume->setPos(sideMargin*2,topMargin*5+unitHeight*2);

            volumeHint = new QGraphicsPixmapItem;
            volumeHint->setPixmap(QPixmap(":/images/pics/MenusAndButtons/volumehint.png"));
            volumeHint->setZValue(1);
            volumeHint->setPos(170,topMargin*8+unitHeight*2);

            connect(this->BGMslider,SIGNAL(sliderMoved(int)),this,SLOT(changeBGMvolume(int)));
            connect(this->SEslider,SIGNAL(sliderMoved(int)),this,SLOT(changeSEvolume(int)));

            settingsScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(settingsScene);
            setFixedSize(GameMenuSize,GameMenuSize);

            settingsScene->addItem(settingsBackground);
            settingsScene->addItem(muteBGMButton);
            settingsScene->addItem(muteSEButton);
            settingsScene->addItem(backButton);
            settingsScene->addWidget(BGMslider);
            settingsScene->addWidget(SEslider);
            settingsScene->addItem(bgmVolume);
            settingsScene->addItem(seVolume);
            settingsScene->addItem(volumeHint);

            settings->setSettingsSceneAlreadyCreated(true);

        } else if((item == this->settingsButton)&&(settings->getSettingsSceneAlreadyCreated()))
        {

            settingsScene->addItem(backButton);
            setScene(settingsScene);
        } else if(item == this->aboutButton)                            // Open about.
        {

        } else if (item == this->exitButton)                            // Exit the game.
        {
            QApplication::quit();
        } else if (item == this->muteBGMButton)                         // Mute BGM
        {
            settings->setBGMMuted(!settings->getBGMMuted());
            if(settings->getBGMMuted())
            {
                soundpointer->BGMplayer->stop();
                muteBGMButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/unmuteBGM.png"));
            }
            if(!settings->getBGMMuted())
            {
                soundpointer->BGMplayer->play();
                muteBGMButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/muteBGMnew.png"));
            }
        } else if (item == this->muteSEButton)                          // Mute SE
        {
            settings->setSEMuted(!settings->getSEMuted());
            switch(settings->getSEMuted())
            {
            case true:
                muteSEButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/unmuteSE.png"));
                break;
            case false:
                muteSEButton->setPixmap(QPixmap(":/images/pics/MenusAndButtons/muteSEnew.png"));
                break;
            }
        } else if (item == this->friendlyFireButton)                    // Switch friendly fire.
        {
            settings->setFrendlyFire(!settings->getFrendlyFire());
            switch(settings->getFrendlyFire())
            {
            case true:
                yesorno->setPixmap(QPixmap(":/images/pics/MenusAndButtons/yes.png"));
                break;
            case false:
                yesorno->setPixmap(QPixmap(":/images/pics/MenusAndButtons/no.png"));
                break;
            }
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

/** @brief GameMenu::getWhichStage() returns the index of the currently selected stage.
 * @return index of the current stage.
 */

int GameMenu::getWhichStage() const
{
    return whichStage;
}

/** @brief GameMenu::setNumberPictureOnPixmap(int number, QGraphicsPixmapItem *pixmap) sets the number on number indicators.
 * @param wished number
 * @param wished number indicator
 */

void GameMenu::setNumberPictureOnPixmap(int number, QGraphicsPixmapItem *pixmap)
{
    switch(number)
    {
    case 1:
        pixmap->setPixmap(QPixmap(":/images/1.png"));
        break;
    case 2:
        pixmap->setPixmap(QPixmap(":/images/2.png"));
        break;
    case 3:
        pixmap->setPixmap(QPixmap(":/images/3.png"));
        break;
    case 4:
        pixmap->setPixmap(QPixmap(":/images/4.png"));
        break;
    case 0:
        pixmap->setPixmap(QPixmap(":/images/pics/0.png"));
        break;
    }
}

/** @brief GameMenu::playeronewon() triggers once the physics calculator says the game is over and player red has won. It shows the end-game scene, then deletes the game scene
 * with it's children.
 */

void GameMenu::playeronewon()
{
    endScene = new QGraphicsScene;

    endSceneBackground = new QGraphicsPixmapItem;
    endSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

    playeronewinsPic = new QGraphicsPixmapItem;
    playeronewinsPic->setPixmap(QPixmap(":/images/pics/MenusAndButtons/PlayerBlueWins.png"));
    playeronewinsPic->setPos(sideMargin,topMargin+settings->getGameWorldSize()/4);

    endScene->addItem(endSceneBackground);
    endScene->addItem(playeronewinsPic);
    endScene->addItem(backButton);

    this->setScene(endScene);
    delete reference;
    gamealreadyexist = false;

    soundpointer->playMenuBGM();
}
/** @brief GameMenu::playertwowon() triggers once the physics calculator says the game is over and player blue has won. It shows the end-game scene, then deletes the game scene
 * with it's children.
 */

void GameMenu::playertwowon()
{
    endScene = new QGraphicsScene;

    endSceneBackground = new QGraphicsPixmapItem;
    endSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

    playertwowinsPic = new QGraphicsPixmapItem;
    playertwowinsPic->setPixmap(QPixmap(":/images/pics/MenusAndButtons/PlayerRedWins.png"));
    playertwowinsPic->setPos(sideMargin,topMargin+settings->getGameWorldSize()/4);

    endScene->addItem(endSceneBackground);
    endScene->addItem(playertwowinsPic);
    endScene->addItem(backButton);

    this->setScene(endScene);
    delete reference;
    gamealreadyexist = false;
    soundpointer->playMenuBGM();
}

/** @brief GameMenu::changeBGMvolume(int volume) sets the volume of the background music to the given number.
 * @param wished volume.
 */

void GameMenu::changeBGMvolume(int volume)
{
    settings->setBGMvolume(volume);
    soundpointer->BGMplayer->setVolume(settings->getBGMvolume());
}

/** @brief GameMenu::changeSEvolume(int volume) sets the volume of sound effects to the given number.
 * @param wished volume
 */

void GameMenu::changeSEvolume(int volume)
{
    settings->setSEvolume(volume);
}

