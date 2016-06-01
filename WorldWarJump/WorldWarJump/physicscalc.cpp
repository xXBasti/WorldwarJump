#include "physicscalc.h"
//#include <QtMath>
#include <cmath>

#define M_PI 3.14159

PhysicsCalc::PhysicsCalc()
{
}
/**
* @brief PhysicsCalc::calculateNewValues calculates the next position of the given WorldObject
* based on it's current position and on its current speed.
* Then it sets the object's new position and new speed
* @param worldObject the WorldObject instance for which new position
*/
void PhysicsCalc::calculateNewValues(WorldObject * worldObject) {
    worldObject->setPos(worldObject->x()+1, worldObject->y()+1);
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
