#include "gamemenu.h"
#include "worldobject.h"
#include "gameworld.h"
#include "mainwindow.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>

#define M_PI 3.14159

GameMenu::GameMenu()
{
    setGameMenuSize(700);

    startScene = new QGraphicsScene;
    menubackground = new QGraphicsPixmapItem;
    menubackground->setPixmap(QPixmap(":/images/menubackground.png"));

    startButton = new QGraphicsPixmapItem;
    startButton->setPixmap(QPixmap(":/images/startbutton.png"));
    startButton->setPos(100,300);
    settingsButton = new QGraphicsPixmapItem;
    exitButton = new QGraphicsPixmapItem;

    startScene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
    setScene(startScene);
    setFixedSize(700,700);


    startScene->addItem(menubackground);
    startScene->addItem(startButton);


    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);





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
            //qDebug()<<"start";
            GameWorld *world = new GameWorld;
            world->show();
            this->destroy();

        }
    }
}

