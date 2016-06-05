#include "physicscalc.h"
//#include <QtMath>
#include <cmath>
#include <QList>
#include "gameworld.h"
#include "terrain.h"
#include <typeinfo>
#include <QDebug>

#include <stdlib.h>
#include <ctime>

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
    if (CollideWithTerrain(worldObject) ){

        double norm = vectorsAbsoluteValue(worldObject->getSpeed());
        worldObject->getSpeed()[1] = 0.001*((worldObject->y()-350)/norm)*worldObject->getSpeed()[1];
        worldObject->getSpeed()[0] = 0.001*((worldObject->x()-350)/norm)*worldObject->getSpeed()[0];

        worldObject->setRotVel(-0.85*worldObject->getRotVel());
        std::srand(std::time(0));
        int random_var = static_cast<int>(((rand()%2) -0.5)*2);
        worldObject->setRotVel(random_var*5 + worldObject->getRotVel());
        worldObject->collidedBefore = 1;

    }else if(!(CollideWithTerrain(worldObject))) worldObject->collidedBefore = 0;


    if (CollideWithTerrain(worldObject) == true)  //Collision detection - WANG
    {
        //worldObject->setPos(worldObject->x(),worldObject->y());
        //worldObject->setSpeed(0);
        qDebug()<<"Collision!";

    }

    //THIS SHIT SUCKS.


    double * speed = worldObject->getSpeed();
  //qDebug() << speed[0] << speed[1];
    double eulPos[2]= {0};
    double polSpeed[2]= {0};

    double polPos[2]= {0};
   /* this->eulToPol(eulPos,polPos,'p');
    this->eulToPol(speed,polSpeed,'v');
    qDebug() << polSpeed[0] << polSpeed[1];
    polSpeed[0]=polSpeed[0]+gravity;
    this->polToEul(polSpeed,speed,'v');
     */
    eulPos[0] = worldObject->x();
    eulPos[1] = worldObject->y();
    speed[0]=speed[0]+((eulPos[0]-350)/350);
    speed[1]=speed[1]+((eulPos[1]-350)/350);
    worldObject->setPos(eulPos[0]+timeStep*speed[0],
                        eulPos[1]+timeStep*speed[1]);
    qDebug() <<"\n\n";
    //speed[1] = speed[1]+gravity;
    //speed[0]=speed[0]+gravity*polPos[1];
    worldObject->setSpeed(speed);
    qDebug() << speed[0] << speed[1];
    return;
}

double PhysicsCalc::vectorsAbsoluteValue(double *vector)
{
    return sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
}
/**
 * @brief PhysicsCalc::eulToPol
 * @param eul
 * @param pol
 */

void PhysicsCalc::eulToPol(double * eul, double* pol,char type){
    double e1;
    double e2;
    switch(type){
    case 'p':
        e1=eul[0]-350; //350 später gamesize/2
        e2=eul[1]-350; // damit polar kosi in der Mitte des Bildschirms ist.
        break;
    case 'v':
        e1=eul[0];
        e2=eul[1];
        break;
    default:
        e1=eul[0];
        e2=eul[1];
        break;
    }


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
        if(e2==0){
            pol[1]=0;
        }
    }
}

/**
 * @brief PhysicsCalc::polToEul
 * @param pol
 * @param eul
 */
void PhysicsCalc::polToEul(double * pol, double* eul,char type){
    switch(type){
    case 'p':
        eul[0]=round(pol[0]*cos(pol[1])*100)/100+350;
        eul[1]=round(pol[0]*sin(pol[1])*100)/100+350;
        break;
    case 'v':
        eul[0]=round(pol[0]*cos(pol[1])*100)/100;
        eul[1]=round(pol[0]*sin(pol[1])*100)/100;
        break;
    default:
        eul[0]=round(pol[0]*cos(pol[1])*100)/100;
        eul[1]=round(pol[0]*sin(pol[1])*100)/100;
        break;
    }


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
