#include "projectile.h"
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <iostream>
#include <time.h>
#include <QtMath>

//Projectile::Projectile(GameWorld *parentView, int x,int y,double dir,ProjectileType p) : WorldObject(parentView)
//{
//    qDebug() << "Launched";
//    this->parentView = parentView;
//    setPixmap(QPixmap(":/images/redrocked70.png"));
//    setTransformOriginPoint(1, 1);
//    this->setPos(x,y);
//    parentView->scene->addItem(this);
//    int rx=0;
//    int ry=0;
//    double velocity[2]={0};
//    qDebug() << "Launching"<< p << dir;
//    /*
//    switch(p){
//    case missile:
//        rx=5;
//        ry=2;
//        velocity[0]=5*sin(dir);
//        velocity[1]=5*cos(dir);
//        break;
//    case balistic:
//        rx=2;
//        ry=2;
//        velocity[0]=10*sin(dir);
//        velocity[1]=10*cos(dir);
//        break;
//    case ray:
//        rx=3;
//        ry=1;
//        velocity[0]=15*sin(dir);
//        velocity[1]=15*cos(dir);
//        break;
//    case scrap:
//        rx=3;
//        ry=3;
//        velocity[0]=10*sin(dir);
//        velocity[1]=10*cos(dir);
//        break;
//    }
//    */
//    velocity[0]=20*sin(dir); //parameter
//    velocity[1]=20*cos(dir);
//    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(move()));
//  /*  QPainter painter(parentView);
//    painter.setBrush(QBrush(Qt::black)); //Je nach typ
//    painter.drawEllipse(QPoint(x,y),rx,ry); */
//    this->setSpeed(velocity);
//    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(hit()));
//}

Projectile::Projectile(GameWorld *parentView, WorldObject *shootingUnit) :WorldObject(parentView, getPlayer()){
    double x = shootingUnit->x();
    double y = shootingUnit->y();
    double dir = shootingUnit->getOrientation()*(M_PI/180);
    this->parentView = parentView;
    setPicture(shootingUnit->getPlayer());
    setTransformOriginPoint(1, 1);
    this->setPos(x,y);
    parentView->scene->addItem(this);
    double velocity[2]={0};
    velocity[0]=20*sin(dir); //parameter
    velocity[1]=20*cos(dir);
    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(move()));
    this->setSpeed(velocity);
    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(hit()));
}

void Projectile::setPicture(Player p)
{
    switch(p){
        case player1:
            setPixmap(QPixmap(":/images/redrocked70.png"));
            break;
        case player2:
            setPixmap(QPixmap(":/images/bluerocked100.png"));
            break;
    default:
        break;
    }
}

Projectile::~Projectile(){


}

void Projectile::fly(){



}


