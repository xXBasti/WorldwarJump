#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <cmath>
#include <QDebug>
#include "input.h"
#include "worldobject.h"
#include "physicscalc.h"
#include "gameworld.h"
#include "gamemenu.h"

#define M_PI 3.14159

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameMenu *menu = new GameMenu();

/*
    MainWindow *w = new MainWindow;
    GameWorld *world = new GameWorld;
    w->setCentralWidget(world);
    w->show();
*/


    return a.exec();
}
