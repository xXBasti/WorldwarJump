#include "projectile.h"
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <iostream>
#include <time.h>
#include <cmath>
#include "physicscalc.h"
#include "GameplayInterface.h"
#include "battleunit.h"
#define M_PI 3.14159

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
//    this->setSpeed(velocity);
//    connect(parentView->input->timer, SIGNAL(timeout()),this , SLOT(hit()));
//}

Projectile::Projectile(GameWorld *parentView, BattleUnit *shootingUnit,ProjectileType p,SoundPlayer *soundplayer , double *shootingPoint) :WorldObject(parentView, getPlayer(),soundplayer){

    ObjectType = 'p';

    int x = static_cast<int>(shootingPoint[0]);
    int y = static_cast<int>(shootingPoint[1]);
    this->shootingUnit=shootingUnit;
    this->pT=p;
//    qDebug() <<"launch";

    //Projectile angle
    double speedPol[2] = {0};
    double speedEul[2] = {0};
    unitType Type = shootingUnit->getUnittype();

    switch(Type){
        case Tank:

            speedPol[0] = 10;
            speedPol[1] = ((shootingUnit->getOrientation()-30)/180)*M_PI;
            break;
        case Soldier:

            speedPol[0] = 10;
            speedPol[1] = ((shootingUnit->getOrientation()-90)/180)*M_PI;
            break;
        case Ship:

            speedPol[0] = 12;
            speedPol[1] = ((shootingUnit->getOrientation()-165)/180)*M_PI;
            break;
    }


    polToEul(speedPol,speedEul,'v');
    //Projectile angle

    this->parentView = parentView;
    switch(p){ //parameter
        case missile:

            speedPol[0] = speedPol[0] * 2;
            this->setDamage(10);
            this->setWeight(10);
            break;
        case balistic:

            speedPol[0] = speedPol[0] * 3;
            this->setDamage(5);
            this->setWeight(5);
            break;
        case ray:

            speedPol[0] = speedPol[0] * 4;
            this->setDamage(8);
            this->setWeight(2);
            break;
        case scrap:

            speedPol[0] = speedPol[0] * 1;
            break;
    }

    setPicture(shootingUnit->getPlayer());
    this->p=shootingUnit->getPlayer();
    setTransformOriginPoint((this->pixmap().width())/2,(this->pixmap().height())/2);
    this->setRotVel(0);
    this->setRotation(speedPol[1]*(180/M_PI));
    this->setHealthpoints(1);

    this->setOrientation(speedPol[1]*(180/M_PI));

    parentView->scene->addItem(this);
    this->setPos(x,y);

    connect(parentView->input->refreshRateTimer, SIGNAL(timeout()),this , SLOT(move()));
    this->setSpeed(speedEul);
    connect(parentView->input->refreshRateTimer, SIGNAL(timeout()),this , SLOT(hit()));
    recoil(shootingUnit,this);

    //qDebug() << "Shooting unit orientation: " << shootingUnit->getOrientation() ;
    //qDebug() << "Projectile orientation: " << speedPol[1]*(180/M_PI) ;
    //qDebug() << shootingUnit->getUnittype() << "  X: " << x << "Y: " << y;
}

void Projectile::setPicture(Player p)
{
    switch(this->pT){
    case missile:
        switch(p){
            case player1:
                setPixmap(QPixmap(":/images/redrocked70.png"));
                break;
            case player2:
                setPixmap(QPixmap(":/images/bluerocked100.png"));
                break;
        }
        break;
    case balistic:
        switch(p){
            case player1:
                setPixmap(QPixmap(":/images/redrocked70.png"));
                break;
            case player2:
                setPixmap(QPixmap(":/images/bluerocked100.png"));
                break;
        }
        break;
    case ray:
        switch(p){
            case player1:
                setPixmap(QPixmap(":/images/ray_red.png"));
                break;
            case player2:
                setPixmap(QPixmap(":/images/ray_blue.png"));
                break;
        }
        break;
    case scrap:
        switch(p){
            case player1:
                setPixmap(QPixmap(":/images/redrocked70.png"));
                break;
            case player2:
                setPixmap(QPixmap(":/images/bluerocked100.png"));
                break;
        }
        break;
    }
}



Projectile::~Projectile(){
}


void Projectile::recoil(WorldObject* obj1, WorldObject* obj2){
    double* v1=obj1->getSpeed();
    double* v2=obj2->getSpeed();
    double v1s[2];
    int m1=obj1->getWeight();
    int m2=obj2->getWeight();
    v1s[0]= v1[0];
    v1s[1]= v1[1];

    v1s[0]=(m1*v1[0]-m2*v2[0])/m1;
    v1s[1]=(m1*v1[0]-m2*v2[0])/m1;
    obj1->setSpeed(v1s);
}

void Projectile::polToEul(double * pol, double* eul,char type){
    switch(type){
    case 'p':
        eul[0]=round(pol[0]*cos(pol[1])*100)/100+400;
        eul[1]=(round(pol[0]*sin(pol[1])*100)/100+400);
        break;
    case 'v':
        eul[0]=round(pol[0]*cos(pol[1])*100)/100;
        eul[1]=(round(pol[0]*sin(pol[1])*100)/100);
        break;
    default:
        eul[0]=round(pol[0]*cos(pol[1])*100)/100;
        eul[1]=round(pol[0]*sin(pol[1])*100)/100;
        break;
    }
}

WorldObject *Projectile::getshootingUnit()
{
    return this->shootingUnit;
}


