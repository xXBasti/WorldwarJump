#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include "input.h"

#include "gameworld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    GameWorld *world = new GameWorld();

    Input * input = new Input();
    world->scene->addItem(input);

    w.setCentralWidget(world);

    //world -> show();

    w.show();
    return a.exec();
}
