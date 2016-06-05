#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

#include "physicscalc.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

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
    speed[1] = -8;
    //double speedPol[2];
    //double speedEul[2];
    //speedPol[0] = sqrt(speed[1]*speed[1] + speed[0]*speed[0]);
    //speedPol[1] = orientation

    //((GameplayInterface*)scene())->physicsCalulator->polToEul(speedAbs,);

    //Create a randm variable that gives -1 or 1
    std::srand(std::time(0));
    int random_var = static_cast<int>(((rand()%2) -0.5)*2);
    qDebug() << random_var;
    //Introduce chance in rotation
    rotVel = random_var *15 + rotVel;
}

WorldObject::WorldObject(GameWorld * parentView) {
    this->parentView = parentView;
    setRect(0,0,50,100);
    setTransformOriginPoint(rect().width()/2, rect().height()/2);
    connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(jump()));
    connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(jump()));
    connect(parentView->input->timer, SIGNAL(timeout()), this, SLOT(move()));//Better use world timer, do we need input timer at all?
    setFlag(QGraphicsItem::ItemIsFocusable);
}


double * WorldObject::getSpeed(){
    return speed;
}

void WorldObject::getNewValuesFromPhysicsCalc()
{
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewValues(this);
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewRotValues(this);
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
