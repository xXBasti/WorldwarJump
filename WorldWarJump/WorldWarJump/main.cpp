#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include "input.h"
#include "worldobject.h"

#include "gameworld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    GameWorld *world = new GameWorld();

    WorldObject * player1Unit1 = new WorldObject(world->input);
    player1Unit1->setPos(100,100);
    world->scene->addItem(player1Unit1);

    w.setCentralWidget(world);

    //world -> show();

    w.show();
    return a.exec();
}
