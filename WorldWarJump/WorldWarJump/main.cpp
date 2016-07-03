#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <QtMath>
#include <QDebug>
#include "input.h"
#include "worldobject.h"
#include "physicscalc.h"
#include "gameworld.h"
#include "gamemenu.h"

//#define M_PI 3.14159

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SoundPlayer *sound = new SoundPlayer;
    new GameMenu(sound);

    return a.exec();
}
