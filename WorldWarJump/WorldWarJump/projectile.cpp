#include "projectile.h"
#include <QPainter>

Projectile::Projectile(GameWorld *parentView, int x,int y,double dir,projectileType pT) : WorldObject(parentView)
{
    int rx,ry;
    double velocity[2]={0};
    switch (pT){
    case missile:
        rx=5;
        ry=2;
        velocity[0]=5*sin(dir);
        velocity[1]=5*cos(dir);
        break;
    case balistic:
        rx=2;
        ry=2;
        velocity[0]=10*sin(dir);
        velocity[1]=10*cos(dir);
        break;
    case ray:
        rx=3;
        ry=1;
        velocity[0]=15*sin(dir);
        velocity[1]=15*cos(dir);
        break;
    case scrap:
        rx=3;
        ry=3;
        velocity[0]=10*sin(dir);
        velocity[1]=10*cos(dir);
        break;
    }

    QPainter painter(parentView);
    painter.setBrush(QBrush(Qt::black)); //Je nach typ
    painter.drawEllipse(QPoint(x,y),rx,ry);
    this->setSpeed(velocity);
}

Projectile::~Projectile(){


}

void Projectile::fly(){



}

void Projectile::hit(){


}
