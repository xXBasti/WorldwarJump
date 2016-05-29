#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>

#include "gameworld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    GameWorld *world = new GameWorld;
    world -> show();


    return a.exec();
}
