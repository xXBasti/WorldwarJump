#define _USE_MATH_DEFINES
#include <cmath>

#include "battleunit.h"
#include "projectile.h"
#include <QDebug>

BattleUnit::BattleUnit(GameWorld * parentView, Player p,SoundPlayer *soundplayer, unitType unittype) : WorldObject(parentView, p,soundplayer)
{
    soundpointer = soundplayer;
    ObjectType = 'b';
    this->parentView = parentView;
    this->ut=unittype;
    setPicture();
    this->setProjectile(0);
    double newCenter[2];

    switch(this->ut){
        case Tank:

            newCenter[0] = 30/*this->pixmap().width()*(30/100)*/;
            newCenter[1] = 20/*this->pixmap().height()*(20/61)*/;
            break;
        case Soldier:

            newCenter[0] = this->pixmap().width();
            newCenter[1] = this->pixmap().height();
            break;
        case Ship:

            newCenter[0] = 60/*this->pixmap().width()*(60/100)*/;
            newCenter[1] = 20/*this->pixmap().height()*(20/62)*/;
            break;
    }

    setCenterOfMass(newCenter);
    setTransformOriginPoint(getCenterOfMass()[0], getCenterOfMass()[1]);

    switch(p){
        case player1:
            connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(shoot()));

        break;
        case player2:
            connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(shoot()));
        break;
    }
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));
    this->p=p;
    this->setWeight(100);
    this->setDamage(5);
    this->setHealthpoints(100);
    this->setRotVel(0);
    //Better use world timer, do we need input timer at all?
    setFlag(QGraphicsItem::ItemIsFocusable);
}


double BattleUnit::getFiredirection(){
    return this->firedirection;
}

void BattleUnit::setFiredirection(double direction){
    this->firedirection=direction;
}

unitType BattleUnit::getUnittype()
{
    return this->ut;
}

void BattleUnit::calculateShootingPoint(double * Point)
{

    unitType u = getUnittype();
    QPointF qpoint;
    switch(u){
        case Tank:

            //qpoint = this->sceneTransform().map(QPointF(this->pixmap().width(),this->pixmap().height()));
            qpoint = this->sceneTransform().map(QPointF(130,12));
            break;
        case Soldier:

            qpoint = this->sceneTransform().map(QPointF(this->pixmap().width(),this->pixmap().height()));
            break;
        case Ship:

            qpoint = this->sceneTransform().map(QPointF(-10,20));
            break;
    }

    Point[0] = qpoint.x();
    Point[1] = qpoint.y();
}

void BattleUnit::setPicture()
{
    Player p = getPlayer();
    unitType u= getUnittype();
    switch(p){
        case player1:
            switch(u){
                case Tank:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Soldier:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Ship:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
            }
        break;
        case player2:
            switch(u){
                case Tank:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Soldier:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Ship:
                    setPixmap(QPixmap(":/images/blueship100.png"));
                break;
            }
        break;
    }
}

void BattleUnit::shoot(){
   // qDebug() <<"fire"<<this->getProjectile();
    soundpointer->playShoot();
    double nozzle[2];
    calculateShootingPoint(nozzle);

    switch(this->getProjectile()%2){
    case 0:
        new Projectile(parentView, this, balistic, soundpointer, nozzle);
        break;
    case 1:
        new Projectile(parentView, this, ray, soundpointer ,nozzle);
        break;
    case 2:
        new Projectile(parentView, this, missile, soundpointer, nozzle);
        break;
    }
}
