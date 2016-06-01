#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"
#include "gameworld.h"
#include "physicscalc.h"

void WorldObject::move()
{
    if (1){
    getNewValuesFromPhysicsCalc();
    for (double c: speed)
        c = 0;
    }
}

void WorldObject::jump()
{
    speed[1] = -15;
}

WorldObject::WorldObject(GameWorld * parentView) {
    setRect(0,0,50,50);
    connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(jump()));
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));
    this->input = parentView->input;
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
