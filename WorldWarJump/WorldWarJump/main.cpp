#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>

#include "gameworld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    GameWorld *world = new GameWorld;

    w.setCentralWidget(world);


    w.show();
    return a.exec();
}
