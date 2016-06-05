#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

#include "physicscalc.h"

/**
 * @brief WorldObject::move
 *
 */
void WorldObject::move()
{
    getNewValuesFromPhysicsCalc();
}

void WorldObject::jump()
{
    speed[1] = -15;
}

WorldObject::WorldObject(GameWorld * parentView) {
    this->parentView = parentView;
    setRect(0,0,50,50);
    connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(jump()));
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));
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


//For Orientation
void WorldObject::setOrientation(double newOrientation)
{
    this->orientation = newOrientation;

}

double WorldObject::getOrientation() const
{
    return(orientation);
}

void WorldObject::setRotVel(double newRotVel)
{
    this->rotVel = newRotVel;
}

double WorldObject::getRotVel() const
{
    return(rotVel);
}
//For Orientation
