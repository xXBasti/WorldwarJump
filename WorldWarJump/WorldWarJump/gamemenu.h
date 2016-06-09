#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QInputEvent>

#include "mainwindow.h"

class GameMenu : public QGraphicsView
{
    Q_OBJECT
public:
    GameMenu();
    MainWindow *w = new MainWindow;


    QGraphicsScene *startScene;
    QGraphicsScene *beforeGameScene;
    QGraphicsPixmapItem *menubackground;

    QGraphicsPixmapItem *startButton;
    QGraphicsPixmapItem *settingsButton;
    QGraphicsPixmapItem *exitButton;


    int getGameMenuSize() const;
    void setGameMenuSize(int value);
    void mousePressEvent(QMouseEvent *event);

private:
    int GameMenuSize;



};

#endif // GAMEMENU_H
