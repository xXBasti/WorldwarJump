#include "physicscalc.h"
//#include <QtMath>
#include <cmath>
#include <QList>
#include "gameworld.h"
#include "terrain.h"
#include <typeinfo>
#include <QDebug>

#define M_PI 3.14159

PhysicsCalc::PhysicsCalc()
{
}

/**
* @brief PhysicsCalc::calculateNewRotValues calculates the next orientation of the given WorldObject
* based on it's current orientation and its current angular velocity.
* Angular array stores in the following order, the angle and angular velocity
* @param the worldobject to be calculated
*/
void PhysicsCalc::calculateNewRotValues(WorldObject * worldObject)
{
    double angular[2];
    angular[0] = worldObject->getOrientation();
    angular[1] = worldObject->getRotVel();

    worldObject->setRotation(angular[0] + timeStep*angular[1]);
    angular[0] = angular[0] + timeStep*angular[1];
    if(angular[0] > 360){
        //angular[0] = (static_cast<double>((static_cast<int>angular[0])%360));
        angular[0] = angular[0] - 360;
    }
    angular[1] = exp(-(timeStep/30))*angular[1];

    updateRotValues(worldObject, angular);
}
/**
 * @brief PhysicsCalc::updateRotValues sets the objects new orientation and new angular velocity
 * @param the Worldobject to be updated
 */
void PhysicsCalc::updateRotValues(WorldObject * worldObject, double *angular)
{
    worldObject->setOrientation(angular[0]);
    worldObject->setRotVel(angular[1]);
}
/**
* @brief PhysicsCalc::calculateNewValues calculates the next position of the given WorldObject
* based on it's current position and its current speed.
* Then it sets the object's new position and new speed
* When the WorldObject moves below the ground (collision) the movement speed of the WorldObject is inverted
* @param worldObject the WorldObject instance for which new position
*/
void PhysicsCalc::calculateNewValues(WorldObject * worldObject) {
    if (CollideWithTerrain(worldObject)){
        worldObject->getSpeed()[1] = -0.85*worldObject->getSpeed()[1];
    }


    if (CollideWithTerrain(worldObject) == true)  //Collision detection - WANG
    {
        //worldObject->setPos(worldObject->x(),worldObject->y());
        //worldObject->setSpeed(0);
        qDebug()<<"Collision!";

    }

    //THIS SHIT SUCKS.


    double * speed = worldObject->getSpeed();
    double xPos = worldObject->x();
    double yPos = worldObject->y();
    worldObject->setPos(xPos+timeStep*speed[0],
                        yPos+timeStep*speed[1]);
    speed[1] = speed[1]+gravity;
    worldObject->setSpeed(speed);
    return;
}
/**
 * @brief PhysicsCalc::eulToPol
 * @param eul
 * @param pol
 */

void PhysicsCalc::eulToPol(double * eul, double* pol){
    double e1=eul[0]-350;
    double e2=eul[1]-350;
    pol[0]=sqrt(e1*e1+e2*e2);
    if(e1>0){
        if(e2>=0){
            pol[1]=atan(e2/e1);
        }
        if(eul[1]<0){
            pol[1]=atan(e2/e1+2*M_PI);
        }
    }
    if(e1<0){
        pol[1]=atan(e2/e1+M_PI);
    }
    if(e1==0){
        if(e2>0){
           pol[1]=M_PI/2;
        }
        if(e2<0){
            pol[1]=((3*M_PI)/2);
        }
    }
}

/**
 * @brief PhysicsCalc::polToEul
 * @param pol
 * @param eul
 */
void PhysicsCalc::polToEul(double * pol, double* eul){
    eul[0]=round(pol[0]*cos(pol[1])*100)/100;
    eul[1]=round(pol[0]*sin(pol[1])*100)/100;
}

bool PhysicsCalc::CollideWithTerrain(WorldObject* object)
{
    QList<QGraphicsItem *> colliding_items = object->collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid(*(colliding_items[i]))== typeid(Terrain))
        {
            return true;
        }
    }
    return false;

}
