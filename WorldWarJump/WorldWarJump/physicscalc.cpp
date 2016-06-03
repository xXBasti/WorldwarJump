#include "physicscalc.h"
//#include <QtMath>
#include <cmath>
#include <QList>
#include "gameworld.h"
#include "terrain.h"
#include <typeinfo>

#define M_PI 3.14159

PhysicsCalc::PhysicsCalc()
{
}
/**
* @brief PhysicsCalc::calculateNewValues calculates the next position of the given WorldObject
* based on it's current position and on its current speed.
* Then it sets the object's new position and new speed
* When the WorldObject moves below the ground (collision) the movement speed of the WorldObject is inverted
* @param worldObject the WorldObject instance for which new position
*/
void PhysicsCalc::calculateNewValues(WorldObject * worldObject) {
    if (worldObject->parentView->getGameWorldSize() <  worldObject->y() + worldObject->rect().height()){
        worldObject->getSpeed()[1] = -0.85*worldObject->getSpeed()[1];
    }
    double * speed = worldObject->getSpeed();
    double xPos = worldObject->x();
    double yPos = worldObject->y();
    worldObject->setPos(xPos+timeStep*speed[0],
                        yPos+timeStep*speed[1]);
    speed[1] = speed[1]+gravity;
    worldObject->setSpeed(speed);
}
/**
 * @brief PhysicsCalc::eulToPol
 * @param eul
 * @param pol
 */

void PhysicsCalc::eulToPol(double * eul, double* pol){
    pol[0]=sqrt(eul[0]*eul[0]+eul[1]*eul[1]);
    if(eul[0]>0){
        if(eul[1]>=0){
            pol[1]=atan(eul[1]/eul[0]);
        }
        if(eul[1]<0){
            pol[1]=atan(eul[1]/eul[0]+2*M_PI);
        }
    }
    if(eul[0]<0){
        pol[1]=atan(eul[1]/eul[0]+M_PI);
    }
    if(eul[0]==0){
        if(eul[1]>0){
           pol[1]=M_PI/2;
        }
        if(eul[1]<0){
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
