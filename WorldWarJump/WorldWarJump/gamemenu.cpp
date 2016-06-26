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
    //sound = new QMediaPlayer;
    //playlist = new QMediaPlaylist;

    /*if(!GameSettings::getBGMMuted())
    {
        playlist->addMedia(QUrl("qrc:/sound/sound/gameBGM.wav"));
        playlist->setCurrentIndex(1);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        sound->setPlaylist(playlist);
        sound->play();
    }*/
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
            beforeGameSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

            addPlayer1UnitButton = new QGraphicsPixmapItem;
            addPlayer1UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer1UnitButton->setPos(sideMargin*2+unitWidth,topMargin*4);
            addPlayer1UnitButton->setZValue(1);

            addPlayer2UnitButton = new QGraphicsPixmapItem;
            addPlayer2UnitButton->setPixmap(QPixmap(":/images/addbutton.png"));
            addPlayer2UnitButton->setPos(sideMargin*2+unitWidth,topMargin*5+buttonHeight);
            addPlayer2UnitButton->setZValue(1);

            //////////////////////////////////////////
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

            ///////////////////////////////////////////////


            removePlayer1UnitButton = new QGraphicsPixmapItem;
            removePlayer1UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer1UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*4);
            removePlayer1UnitButton->setZValue(1);

            removePlayer2UnitButton = new QGraphicsPixmapItem;
            removePlayer2UnitButton->setPixmap(QPixmap(":/images/removebutton.png"));
            removePlayer2UnitButton->setPos(sideMargin*3+unitWidth+buttonWidth,topMargin*5+buttonHeight);
            removePlayer2UnitButton->setZValue(1);

            changeStageButton = new QGraphicsPixmapItem;
            changeStageButton->setPixmap(QPixmap("ADD PATH"));
            changeStageButton->setPos(GameMenuSize-sideMargin-buttonWidth,topMargin*4);
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

            ////////////////
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
            //////////////////////////////////////////////

            beforeGameScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(beforeGameScene);
            setFixedSize(GameMenuSize,GameMenuSize);

            beforeGameScene->addItem(beforeGameSceneBackground);
           // beforeGameScene->addItem(addPlayer1UnitButton);
           // beforeGameScene->addItem(addPlayer2UnitButton);
           // beforeGameScene->addItem(removePlayer1UnitButton);
            //beforeGameScene->addItem(removePlayer2UnitButton);
            beforeGameScene->addItem(changeStageButton);
            beforeGameScene->addItem(startBattleButton);
            beforeGameScene->addItem(stagePicture);
            beforeGameScene->addItem(titlePicture);
           // beforeGameScene->addItem(player1UnitPicture);
            //beforeGameScene->addItem(player2UnitPicture);
            beforeGameScene->addItem(backButton);
          //  beforeGameScene->addItem(player1UnitCountPicture);
          //  beforeGameScene->addItem(player2UnitCountPicture);

            ////////////////////////////////////
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
            ////////////////////////

            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);\

            settings->setBeforeGameSceneAlreadyCreated(true);

        } else if((item == this->startButton) && (settings->getBeforeGameSceneAlreadyCreated()))
        {
            beforeGameScene->addItem(backButton);
            setScene(beforeGameScene);
        } else if(item == this->startBattleButton)                      //StartBattleButton Pressed, which means start the game.
        {
            GameWorld *gameScene = new GameWorld(soundpointer);
            connect(gameScene,SIGNAL(playeronewinsSignal()),this,SLOT(playeronewon()));
            connect(gameScene,SIGNAL(playertwowinsSignal()),this,SLOT(playertwowon()));

            this->setScene(gameScene->scene);
            gameScene->scene->addItem(backButton);
            soundpointer->playGameBGM();



        } else if(item == this->addPlayer1UnitButton)                   // Add player1 unit.
        {
            player1UnitCount = settings->getPlayer1UnitCount();
            //qDebug()<<player1UnitCount;
            player1UnitCount++;
            settings->setPlayer1UnitCount(player1UnitCount);
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

        } else if(item == this->addRedShipButton)
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
         } else if(item == this->addRedTankButton)
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
        } else if(item == this->addBlueShipButton)
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
        } else if(item == this->addBlueTankButton)
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

        } else if(item == this->removePlayer2UnitButton)                // Remove player2 unit.
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
        } else if(item == this->removeRedShipButton)
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
        } else if(item == this->removeRedTankButton)
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
        } else if(item == this->removeBlueShipButton)
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
        } else if(item == this->removeBlueTankButton)
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
            if(whichStage == 1) whichStage++;
            if(whichStage == 2) whichStage--;
            settings->setWhichStage(whichStage);

        } else if(item == this->backButton)                             // Go back to main menu.
        {
            setScene(startScene);

        } else if((item == this->settingsButton)&&!(settings->getSettingsSceneAlreadyCreated()))                         // Open settings.
        {
            settingsScene = new QGraphicsScene;
            settingsBackground = new QGraphicsPixmapItem;
            settingsBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

            muteBGMButton = new QGraphicsPixmapItem;
            muteBGMButton->setPixmap(QPixmap(":/images/pics/muteBGM.png"));
            muteBGMButton->setPos(GameMenuSize-sideMargin*2,topMargin*4);
            muteBGMButton->setZValue(1);

            muteSEButton = new QGraphicsPixmapItem;
            muteSEButton->setPixmap(QPixmap(":/images/pics/muteSE.png"));
            muteSEButton->setPos(GameMenuSize-sideMargin*2,topMargin*5+buttonHeight);
            muteSEButton->setZValue(1);

            settingsScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
            setScene(settingsScene);
            setFixedSize(GameMenuSize,GameMenuSize);

            settingsScene->addItem(settingsBackground);
            settingsScene->addItem(muteBGMButton);
            settingsScene->addItem(muteSEButton);
            settingsScene->addItem(backButton);

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
            if(settings->getBGMMuted()) soundpointer->BGMplayer->stop();
            if(!settings->getBGMMuted()) soundpointer->BGMplayer->play();
        } else if (item == this->muteSEButton)                          // Mute SE
        {
            settings->setSEMuted(!settings->getSEMuted());
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

void GameMenu::playeronewon()
{
    endScene = new QGraphicsScene;

    endSceneBackground = new QGraphicsPixmapItem;
    endSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

    playeronewinsPic = new QGraphicsPixmapItem;
    playeronewinsPic->setPixmap(QPixmap(":/images/pics/MenusAndButtons/PlayerOneWins.png"));
    playeronewinsPic->setPos(sideMargin,topMargin+settings->getGameWorldSize()/4);

    endScene->addItem(endSceneBackground);
    endScene->addItem(playeronewinsPic);
    endScene->addItem(backButton);

    this->setScene(endScene);

    soundpointer->playMenuBGM();
}

void GameMenu::playertwowon()
{
    endScene = new QGraphicsScene;

    endSceneBackground = new QGraphicsPixmapItem;
    endSceneBackground->setPixmap(QPixmap(":/images/pics/MenusAndButtons/Menu.png"));

    playertwowinsPic = new QGraphicsPixmapItem;
    playertwowinsPic->setPixmap(QPixmap(":/images/pics/MenusAndButtons/PlayerTwoWins.png"));
    playertwowinsPic->setPos(sideMargin,topMargin+settings->getGameWorldSize()/4);

    endScene->addItem(endSceneBackground);
    endScene->addItem(playertwowinsPic);
    endScene->addItem(backButton);

    this->setScene(endScene);

    soundpointer->playMenuBGM();
}

