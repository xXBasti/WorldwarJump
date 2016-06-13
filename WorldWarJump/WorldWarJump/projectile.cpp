#include "projectile.h"
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <iostream>
#include <time.h>

Projectile::Projectile(GameWorld *parentView, int x,int y,double dir,ProjectileType p) : WorldObject(parentView)
{
    qDebug() << "Launched";
    this->parentView = parentView;

    setTransformOriginPoint(1, 1);
    this->setPos(x,y);
    parentView->scene->addItem(this);
    double velocity[2]={0};
    qDebug() << "Launching"<< p << dir;

    switch(p){
    case missile:      
        velocity[0]=5*sin(dir);
        velocity[1]=5*cos(dir);
        setPixmap(QPixmap(":/images/redrocked70.png"));
        this->damage=10;
        break;
    case balistic:     
        velocity[0]=10*sin(dir);
        velocity[1]=10*cos(dir);
        this->damage=5;
        break;
    case ray:     
        velocity[0]=15*sin(dir);
        velocity[1]=15*cos(dir);
        this->damage=8;
        setPixmap(QPixmap(":/images/projektile.png"));
        break;
    case scrap:
        velocity[0]=10*sin(dir);
        velocity[1]=10*cos(dir);
        break;
    }

    this->setWeight(1);
    this->setRotVel(0);

    velocity[0]=5*sin(dir);
    velocity[1]=5*cos(dir);
    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(move()));
  /*  QPainter painter(parentView);
    painter.setBrush(QBrush(Qt::black)); //Je nach typ
    painter.drawEllipse(QPoint(x,y),rx,ry); */
    this->setSpeed(velocity);
    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(hit()));
}

Projectile::~Projectile(){


}

void Projectile::fly(){



}


