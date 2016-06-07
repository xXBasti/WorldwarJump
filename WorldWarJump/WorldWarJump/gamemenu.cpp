#include "gamemenu.h"

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>

GameMenu::GameMenu()
{
    setGameMenuSize(700);

    scene = new QGraphicsScene;
    menubackground = new QGraphicsPixmapItem;
    menubackground->setPixmap(QPixmap(":/images/menubackground.png"));

    startButton = new QGraphicsPixmapItem;
    startButton->setPixmap(QPixmap(":/images/startbutton.png"));
    startButton->setPos(100,300);
    settingsButton = new QGraphicsPixmapItem;
    exitButton = new QGraphicsPixmapItem;

    scene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
    setScene(scene);
    setFixedSize(700,700);


    scene->addItem(menubackground);
    scene->addItem(startButton);


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
        //if(item == startButton)
        //{
            qDebug()<<"Clicked on"<<item;
        //}
    }
}

