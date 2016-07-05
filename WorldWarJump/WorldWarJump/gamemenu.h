#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QInputEvent>
#include <QSlider>
#include <QGraphicsProxyWidget>

#include "mainwindow.h"
#include "gamesettings.h"
#include "soundplayer.h"
#include "gameworld.h"

//!The GameMenu class contains all necessary things for a functional game menu: Pages, buttons and images. It also has parameters which save custom options. - Wang
class GameMenu : public QGraphicsView
{
    Q_OBJECT
public:

    GameMenu(SoundPlayer *soundplayer);
    GameSettings *settings;
    //! because soundplayer is instantiated in main, we need this as a reference to gain access on it.
    SoundPlayer *soundpointer;
    //! used to gain access on created game.
    GameWorld *reference;

    MainWindow *w = new MainWindow;

    //! is the main menu.
    QGraphicsScene *startScene;
    //! is the scene between main menu and game scene.
    QGraphicsScene *beforeGameScene;
    //! is the setting menu for sound.
    QGraphicsScene *settingsScene;
    //! is the about page.
    QGraphicsScene *aboutScene;
    //! is the scene after someone has won.
    QGraphicsScene *endScene;

    //! is the background picture for main menu.
    QGraphicsPixmapItem *startSceneBackground;
    //! is the background picture for pregame settings.
    QGraphicsPixmapItem *beforeGameSceneBackground;
    //! is the background picture for winning scene.
    QGraphicsPixmapItem *endSceneBackground;

    QGraphicsPixmapItem *startButton;
    QGraphicsPixmapItem *settingsButton;
    QGraphicsPixmapItem *aboutButton;
    QGraphicsPixmapItem *exitButton;

    QGraphicsPixmapItem *addPlayer1UnitButton;
    QGraphicsPixmapItem *addPlayer2UnitButton;

    QGraphicsPixmapItem *addRedTankButton; //New
    QGraphicsPixmapItem *addRedShipButton;
    QGraphicsPixmapItem *removeRedTankButton;
    QGraphicsPixmapItem *removeRedShipButton;
    QGraphicsPixmapItem *addBlueTankButton;
    QGraphicsPixmapItem *addBlueShipButton;
    QGraphicsPixmapItem *removeBlueTankButton;
    QGraphicsPixmapItem *removeBlueShipButton;//End new

    QGraphicsPixmapItem *removePlayer1UnitButton;
    QGraphicsPixmapItem *removePlayer2UnitButton;
    QGraphicsPixmapItem *changeStageButton;
    QGraphicsPixmapItem *startBattleButton;
    QGraphicsPixmapItem *backButton;

    QGraphicsPixmapItem *friendlyFireButton;
    QGraphicsPixmapItem *yesorno;

    QGraphicsPixmapItem *player1UnitPicture;
    QGraphicsPixmapItem *player2UnitPicture;
    QGraphicsPixmapItem *stagePicture;
    QGraphicsPixmapItem *titlePicture;
    QGraphicsPixmapItem *player1UnitCountPicture;
    QGraphicsPixmapItem *player2UnitCountPicture;

    QGraphicsPixmapItem *playerRedShipCountPicture; //new
    QGraphicsPixmapItem *playerRedTankCountPicture;
    QGraphicsPixmapItem *playerBlueShipCountPicture;
    QGraphicsPixmapItem *playerBlueTankCountPicture;

    QGraphicsPixmapItem *redShipPicture;
    QGraphicsPixmapItem *redTankPicture;
    QGraphicsPixmapItem *blueShipPicture;
    QGraphicsPixmapItem *blueTankPicture; //end new

    QGraphicsPixmapItem *thumbnail;

    QGraphicsPixmapItem *muteBGMButton;
    QGraphicsPixmapItem *muteSEButton;
    QGraphicsPixmapItem *bgmVolume;
    QGraphicsPixmapItem *seVolume;
    QGraphicsPixmapItem *volumeHint;
    QSlider *BGMslider;
    QSlider *SEslider;

    QGraphicsPixmapItem *settingsBackground;

    QGraphicsPixmapItem *playeronewinsPic;
    QGraphicsPixmapItem *playertwowinsPic;

    int getGameMenuSize() const;
    void setGameMenuSize(int value);
    void mousePressEvent(QMouseEvent *event);

    int getPlayer1UnitCount() const;

    int getPlayer2UnitCount() const;

    int getWhichStage() const;

private:
    int GameMenuSize;
    int sideMargin;
    int topMargin;
    int buttonWidth;
    int buttonHeight;
    int unitWidth;
    int unitHeight;

    int player1UnitCount;
    int player2UnitCount;

    int playerRedTankCount; //new
    int playerRedShipCount;
    int playerBlueTankCount;
    int playerBlueShipCount; //end new

    int whichStage;
    bool gamealreadyexist;
    void setNumberPictureOnPixmap(int number, QGraphicsPixmapItem * pixmap);

public slots:
    void playeronewon();
    void playertwowon();

    void changeBGMvolume(int volume);
    void changeSEvolume(int volume);

};

#endif // GAMEMENU_H
