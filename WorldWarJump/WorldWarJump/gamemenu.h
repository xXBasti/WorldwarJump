#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QInputEvent>
//#include <QMediaPlaylist>

#include "mainwindow.h"
#include "gamesettings.h"
#include "soundplayer.h"

//!The GameMenu class contains all necessary things for a functional game menu: Pages, buttons and images. It also has parameters which save custom options. - WANG
class GameMenu : public QGraphicsView
{
    Q_OBJECT
public:
    GameMenu(SoundPlayer *soundplayer);
    GameSettings *settings;
    //QMediaPlayer *sound;
    //QMediaPlaylist *playlist;
    SoundPlayer *soundpointer;

    //!Mainwindow of WorldWarJump
    MainWindow *w = new MainWindow;

    //!Different Scenes of GameMenu
    QGraphicsScene *startScene;
    QGraphicsScene *beforeGameScene;
    QGraphicsScene *settingsScene;
    QGraphicsScene *aboutScene;
    QGraphicsScene *endScene;

    //!Background pictures
    QGraphicsPixmapItem *startSceneBackground;
    QGraphicsPixmapItem *beforeGameSceneBackground;
    QGraphicsPixmapItem *endSceneBackground;

    //ALL FOLLOWING ICONS (EXCEPT TITLEPIC) ARE SUPPOSED TO BE 50x50

    //!Buttons on startScene
    QGraphicsPixmapItem *startButton;
    QGraphicsPixmapItem *settingsButton;
    QGraphicsPixmapItem *aboutButton;
    QGraphicsPixmapItem *exitButton;

    //!Buttons on beforeGameScene
    QGraphicsPixmapItem *addPlayer1UnitButton;
    QGraphicsPixmapItem *addPlayer2UnitButton;
    QGraphicsPixmapItem *removePlayer1UnitButton;
    QGraphicsPixmapItem *removePlayer2UnitButton;
    QGraphicsPixmapItem *changeStageButton;
    QGraphicsPixmapItem *startBattleButton;
    QGraphicsPixmapItem *backButton;

    //!Pictures on beforeGameScene
    QGraphicsPixmapItem *player1UnitPicture;
    QGraphicsPixmapItem *player2UnitPicture;
    QGraphicsPixmapItem *stagePicture;
    QGraphicsPixmapItem *titlePicture;
    QGraphicsPixmapItem *player1UnitCountPicture;
    QGraphicsPixmapItem *player2UnitCountPicture;

    //!Buttons on settingsScene
    QGraphicsPixmapItem *muteBGMButton;
    QGraphicsPixmapItem *muteSEButton;

    //!Pictures on settingsScene
    QGraphicsPixmapItem *settingsBackground;

    //!Pictures on endScene
    QGraphicsPixmapItem *playeronewinsPic;
    QGraphicsPixmapItem *playertwowinsPic;

    int getGameMenuSize() const;
    void setGameMenuSize(int value);
    void mousePressEvent(QMouseEvent *event);

    int getPlayer1UnitCount() const;

    int getPlayer2UnitCount() const;

    int getWhichStage() const;

private:
    //!Layout sizes
    int GameMenuSize;
    int sideMargin;
    int topMargin;
    int buttonWidth;
    int buttonHeight;
    int unitWidth;
    int unitHeight;

    int player1UnitCount;
    int player2UnitCount;
    int whichStage;

public slots:
    //For the endscreen.
    void playeronewon();
    void playertwowon();

};

#endif // GAMEMENU_H
