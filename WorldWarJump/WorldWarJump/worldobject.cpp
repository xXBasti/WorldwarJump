#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

void WorldObject::move()
{
    qDebug() << "Qtimer refreshing move()";
    getNewValuesFromPhysicsCalc();
}

void WorldObject::jump()
{
    speed[0] = 1;
    speed[1] = 1;
}

WorldObject::WorldObject(Input* passInput)
{
    setRect(0,0,700,700);
    connect(passInput, SIGNAL(playerOneJump()), this, SLOT(jump()));
    connect(passInput, SIGNAL(playerTwoJump()), this, SLOT(jump()));
    connect(passInput, SIGNAL(playerOneShoot()), this, SLOT(jump()));
    connect(passInput, SIGNAL(playerTwoShoot()), this, SLOT(jump()));
    connect(passInput->timer, SIGNAL(timeout()), this, SLOT(move()));
    this->input = passInput;
    setFlag(QGraphicsItem::ItemIsFocusable);
}

double * WorldObject::getSpeed(){
    return speed;
}

void WorldObject::getNewValuesFromPhysicsCalc()
{
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewValues(this);
}


void WorldObject::setSpeed(double *newSpeed){
    speed[0] = newSpeed[0];
    speed[1] = newSpeed[1];
}
