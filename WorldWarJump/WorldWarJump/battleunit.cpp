#include "battleunit.h"
#include "projectile.h"

BattleUnit::BattleUnit(GameWorld * parentView,Player p) : WorldObject(parentView)
{
    this->parentView = parentView;
    //setRect(0,0,50,100);
    //setTransformOriginPoint(rect().width()/2, rect().height()/2);
    switch(p){
        case player1:
            connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(jump()));

            break;
        case player2:
            connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(jump()));
    }
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));



    //Better use world timer, do we need input timer at all?
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void BattleUnit::shoot(){
  //  this->pos();
    this->getFiredirection();
  //  Projectile p=new Projectile();



}

double BattleUnit::getFiredirection(){
    return this->firedirection;
}

void BattleUnit::setFiredirection(double direction){
    this->firedirection=direction;
}
