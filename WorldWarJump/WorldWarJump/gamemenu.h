#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class GameMenu : public QGraphicsView
{
public:
    GameMenu();

    QGraphicsScene *scene;
    QGraphicsPixmapItem *menubackground;

    int getGameMenuSize() const;
    void setGameMenuSize(int value);

private:
    int GameMenuSize;

};

#endif // GAMEMENU_H
