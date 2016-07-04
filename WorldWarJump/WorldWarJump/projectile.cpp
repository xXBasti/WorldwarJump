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

/**
 * @brief Projectile::Projectile constructor. Initializes  the position, the initial angle ,
 * the initial speed ,the projectile type , the weight and the damage and connects the timer
 * @param parentView pointer to connect() the BattleUnit to the player's input and the game's refresh rate.
 * @param shootingUnit the battle unit shooting the projectile
 * @param p the enum that gives the projectile type
 * @param soundplayer the pointer to the global sound player
 * @param shootingPoint the point in scene coordinates where the projectile should spawn
 */
Projectile::Projectile(GameWorld *parentView, BattleUnit *shootingUnit,ProjectileType p,SoundPlayer *soundplayer , double *shootingPoint) :WorldObject(parentView, getPlayer(),soundplayer){

    ObjectType = 'p';

    int x = static_cast<int>(shootingPoint[0]);
    int y = static_cast<int>(shootingPoint[1]);
    this->shootingUnit=shootingUnit;
    this->pT=p;
    this->orientationChanged = false;
    this->orientationChangeCount = 0;

    //Projectile angle
    double speedPol[2] = {0};
    double speedEul[2] = {0};
    unitType Type = shootingUnit->getUnittype();

    switch(Type){
        case Tank:

            speedPol[1] = ((shootingUnit->getOrientation()-30)/180)*M_PI;
            break;
        case Soldier:

            speedPol[1] = ((shootingUnit->getOrientation()-90)/180)*M_PI;
            break;
        case Ship:

            speedPol[1] = ((shootingUnit->getOrientation()-145)/180)*M_PI;
            break;
    }



    //Projectile angle

    this->parentView = parentView;
    switch(p){ //parameter
        case missile:

            speedPol[0] = 20;
            this->setDamage(20);
            this->setWeight(20);
            break;
        case balistic:

            speedPol[0] = 28;
            this->setDamage(10);
            this->setWeight(10);
            break;
        case ray:

            speedPol[0] = 35;
            this->setDamage(15);
            this->setWeight(4);
            break;
    }
    polToEul(speedPol,speedEul,'v');
    setPicture(shootingUnit->getPlayer());
    this->p=shootingUnit->getPlayer();
    setTransformOriginPoint(0,0);
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
                setPixmap(QPixmap(":/images/pics/bluerocked70.png"));
                break;
        }
        break;
    case balistic:
        switch(p){
            case player1:
                setPixmap(QPixmap(":/images/pics/UnitsAndProjectiles/kugel20.png"));
                break;
            case player2:
                setPixmap(QPixmap(":/images/pics/UnitsAndProjectiles/kugel20.png"));
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
    v1s[1]=(m1*v1[1]-m2*v2[1])/m1;
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


