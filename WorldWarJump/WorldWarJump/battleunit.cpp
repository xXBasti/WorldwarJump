#define _USE_MATH_DEFINES
#include <cmath>

#include "battleunit.h"
#include "projectile.h"
#include <QDebug>

BattleUnit::BattleUnit(GameWorld * parentView, Player p) : WorldObject(parentView, p)
{
    this->parentView = parentView;
    setPicture();

    double newCenter[2];
    newCenter[0] = 30;
    newCenter[1] = 20;
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

    this->setWeight(100);
    this->damage=0;
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

void BattleUnit::setPicture()
{
    Player p = getPlayer();
    switch(p){
        case player1:
            setPixmap(QPixmap(":/images/redtank100.png"));
            break;
        case player2:
            setPixmap(QPixmap(":/images/blueship100.png"));
            break;
    default:
        break;
    }
}

void BattleUnit::shoot(){
    qDebug() <<"fire";
    new Projectile(parentView, this,balistic);
}
