#include "battleunit.h"
#include "projectile.h"
#include <QDebug>

BattleUnit::BattleUnit(GameWorld * parentView,Player p) : WorldObject(parentView)
{
    this->parentView = parentView;
    setPixmap(QPixmap(":/images/worldobject.png"));
    setTransformOriginPoint(12, 25);
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


    //Better use world timer, do we need input timer at all?
    setFlag(QGraphicsItem::ItemIsFocusable);
}



double BattleUnit::getFiredirection(){
    return this->firedirection;
}

void BattleUnit::setFiredirection(double direction){
    this->firedirection=direction;
}

void BattleUnit::shoot(){
    qDebug() <<"fire";
    double pos[2];
    this->getPosition(pos);
    double dir=this->getFiredirection();
    double orient=this->getOrientation()*(M_PI/180);
    dir=dir+orient;

    Projectile* p=new Projectile(this->parentView,pos[0],pos[1],dir,ray);

}
