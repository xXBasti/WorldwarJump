#include "gamemenu.h"

#include <QGraphicsPixmapItem>

GameMenu::GameMenu()
{
    setGameMenuSize(700);

    scene = new QGraphicsScene;
    menubackground = new QGraphicsPixmapItem;

    scene->setSceneRect(0,0,GameMenuSize,GameMenuSize);
    setScene(scene);
    setFixedSize(700,700);

    menubackground->setPixmap(QPixmap(":/images/menubackground.png"));
    scene->addItem(menubackground);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Input-connection to World scene

}

int GameMenu::getGameMenuSize() const
{
    return GameMenuSize;
}

void GameMenu::setGameMenuSize(int value)
{
    GameMenuSize = value;
}
