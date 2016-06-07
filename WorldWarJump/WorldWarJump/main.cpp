#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <cmath>
#include <QDebug>
#include "input.h"
#include "worldobject.h"
#include "physicscalc.h"
#include "gameworld.h"

#define M_PI 3.14159

int main(int argc, char *argv[])
{
    double e1[2]={300,300};
    double p1[2]={1,M_PI};
    double e2[2]={0};
    double p2[2]={0};

    QApplication a(argc, argv);
    MainWindow w;

    GameWorld *world = new GameWorld();

    WorldObject * player1Unit1 = new WorldObject(world);
    player1Unit1->setPos(350,350);
    world->scene->addItem(player1Unit1);

    w.setCentralWidget(world);
    w.show();

    PhysicsCalc* p= new PhysicsCalc();
    p->eulToPol(e1,p2,'p');
    p->polToEul(p1,e2,'v');

    qDebug() << p2[0] << p2[1];
    qDebug() << e2[0] << e2[1];
    p->eulToPol(e2,p1,'v');
    p->polToEul(p2,e1,'p');
    qDebug() << p1[0] << p1[1];
    qDebug() << e1[0] << e1[1];

    return a.exec();
}
