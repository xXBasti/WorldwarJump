#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

#include "physicscalc.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

#define M_PI 3.14159



/**
 * @brief WorldObject::move
 *
 */
void WorldObject::move()
{
    getNewValuesFromPhysicsCalc();
}
void WorldObject::hit(){
    ((GameplayInterface*)scene())->physicsCalulator->hitUnit(this);


}

void WorldObject::jump()
{
    double eulPosition [2];
    getPosition(eulPosition);
    double radialSpeed [2];

    // transform from eulSpeed to radialSpeed
    ((GameplayInterface*)scene())->physicsCalulator->velocityEulerToRadialCoordinates(eulPosition, speed, radialSpeed, true);
    // radial speed points to the center at collision
    radialSpeed[0] = -7;    // parameter
    radialSpeed[1] = -3;    // parameter
    // transform from radialSpeed to eulSpeed
    ((GameplayInterface*)scene())->physicsCalulator->velocityEulerToRadialCoordinates(eulPosition, radialSpeed, speed, false);
    setSpeed(speed);

    //Create a randm variable that gives -1 or 1
    /*std::srand(std::time(0));
    int random_var = static_cast<int>(((rand()%2) -0.5)*2);
    qDebug() << random_var;*/
    //Introduce chance in rotation
    //rotVel = random_var *1 + rotVel;
    rotVel = 5 + rotVel;
    qDebug() << "Orientation" << orientation;
}


WorldObject::WorldObject(GameWorld * parentView) {
    speed[0] = speed[1] = 0;
    setOrientation(0);
    setRotVel(0);
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

void WorldObject::getPosition(double *outputPointer)
{
    outputPointer[0] = x();
    outputPointer[1] = y();
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

void WorldObject::setHitCounter(int hit)
{
    this->hitcounter=hit;
}

int WorldObject::getHitCounter()
{
    return this->hitcounter;
}
//For Orientation

WorldObject::~WorldObject() {

}

