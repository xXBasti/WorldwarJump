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

<<<<<<< HEAD
    world -> show();
=======
>>>>>>> 074cb69799db12d77dd92167216db74e3eb3cb19

    w.show();
    return a.exec();
}
