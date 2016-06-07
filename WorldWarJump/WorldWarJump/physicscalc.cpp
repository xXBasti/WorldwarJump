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
/*
    if (CollideWithTerrain(worldObject) /&& worldObject->collidedBefore==0/){

        double colSpeed[2]={0};
        colSpeed[0]=worldObject->getSpeed()[0];
        colSpeed[1]=worldObject->getSpeed()[1];
        double colPosEul[2]={0};
        colPosEul[0]=worldObject->x();
        colPosEul[1]=worldObject->x();
        this->radialCollison(colPosEul,colSpeed);
        qDebug() << colSpeed[0] << colSpeed[1];
        worldObject->getSpeed()[0]=colSpeed[0];
        worldObject->getSpeed()[1]=colSpeed[1];

         alt:
        double norm = vectorsAbsoluteValue(worldObject->getSpeed());
        worldObject->getSpeed()[1] = 0.001*((worldObject->y()-350)/norm)*worldObject->getSpeed()[1];
        worldObject->getSpeed()[0] = 0.001*((worldObject->x()-350)/norm)*worldObject->getSpeed()[0];


        worldObject->setRotVel(-0.85*worldObject->getRotVel());
        std::srand(std::time(0));
        int random_var = static_cast<int>(((rand()%2) -0.5)*2);
        worldObject->setRotVel(random_var*5 + worldObject->getRotVel());
        worldObject->collidedBefore = 1;
 */
    if (CollideWithTerrain(worldObject)){

        qDebug()<<"Collision!";
        double * eulSpeed = worldObject->getSpeed();

        double eulPosition [2];
        worldObject->getPosition(eulPosition);
        double radialSpeed [2];


        velocityEulerToRadialCoordinates(eulPosition, eulSpeed, radialSpeed, true);
        radialSpeed[0] = -(0.85*sqrt(radialSpeed[0]*radialSpeed[0])+abs(0.15*radialSpeed[1]));
        radialSpeed[1] = 0.85*radialSpeed[1];
        worldObject->setRotVel(worldObject->getRotVel()-1*radialSpeed[1]); // Parameter: 1

        velocityEulerToRadialCoordinates(eulPosition, radialSpeed, eulSpeed, false);
        worldObject->setSpeed(eulSpeed);


//        std::srand(std::time(0));
//        int random_var = static_cast<int>(((rand()%2) -0.5)*2);
//        worldObject->setRotVel(random_var*5 + worldObject->getRotVel());
    }
    //THIS SHIT SUCKS.

    double * speed = worldObject->getSpeed();

  /*qDebug() << speed[0] << speed[1];
    double eulPos[2]= {0};
    double polSpeed[2]= {0};

    double polPos[2]= {0};

    this->eulToPol(speed,polSpeed,'v');
    qDebug() << polSpeed[0] << polSpeed[1];
    polSpeed[0]=polSpeed[0]+gravity;
    this->polToEul(polSpeed,speed,'v');


    eulPos[0] = worldObject->x();
    eulPos[1] = worldObject->y();
    this->eulToPol(eulPos,polPos,'p');
    speed[0]=speed[0]+((eulPos[0]-350)/350);  // plus halb länge, weil das Koordinatensystem des Körpers oben links ist.
    speed[1]=speed[1]+((eulPos[1]-350)/350);  // plus halbe länge, weil das Koordinatensystem " " ".. bzw. -(350-länge/2))
    worldObject->setPos(eulPos[0]+timeStep*speed[0],
                        eulPos[1]+timeStep*speed[1]);
    qDebug() <<"\n\n";
    //speed[1] = speed[1]+gravity;
    //speed[0]=speed[0]+gravity*polPos[1];
    alt ?*/

    double posCoordinates [2];
    posCoordinates[0] = worldObject->x();
    posCoordinates[1] = worldObject->y();
    worldObject->setPos(posCoordinates[0]+timeStep*speed[0],
                        posCoordinates[1]+timeStep*speed[1]);
    speed[0] = speed[0]+gravity*(posCoordinates[0]-325 )/norm(posCoordinates); //GameWorldSize && GameUnitSize
    speed[1] = speed[1]+gravity*(posCoordinates[1]-300 )/norm(posCoordinates);

    worldObject->setSpeed(speed);

    return;
}


double PhysicsCalc::vectorsAbsoluteValue(double *vector)
{
    return sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
}

double PhysicsCalc::norm(double *vector)
{
    return sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
}

/**
 * @brief PhysicsCalc::velocityEulerToRadialCoordinates
 * @param eulInputPosition objects position
 * @param eulInputVelocity objects velocity
 * @param radialOutput first direction is radial, second directions is tangential
 * @param eulerToRadial true if transforming from euler to radial, or false if transforming from radial to euler
 */
void PhysicsCalc::velocityEulerToRadialCoordinates(double *eulInputPosition, double *inputVelVector, double *outputVelVector, bool eulerToRadial)
{
    double lVector [2];
    lVector[0] = eulInputPosition[0]-350 + (50/2); //GameWorldSize && GameUnitSize
    lVector[1] = 350 - (100/2) - eulInputPosition[1];
    double vecLength = norm(lVector);
    double v_x = inputVelVector[0];
    double v_y = inputVelVector[1];
    if (eulerToRadial){
        outputVelVector[0] = (v_x*lVector[0] - v_y*lVector[1])/vecLength;
        outputVelVector[1] = (v_x*lVector[1] + v_y*lVector[0])/vecLength;
        return;
    } else {
        outputVelVector[0] = (v_x*lVector[0] + v_y*lVector[1])/vecLength;
        outputVelVector[1] = (-v_x*lVector[1] + v_y*lVector[0])/vecLength;
    }

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
        e2=(eul[1]-350); // damit polar kosi in der Mitte des Bildschirms ist.
        break;
    case 'v':
        e1=eul[0];
        e2=(eul[1]);
        break;
    case 'b':
        e1=eul[0]-350;
        e2=-(eul[1]-350);
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
            pol[1]=atan(e2/e1)+2*M_PI;
        }
    }
    if(e1<0){
        pol[1]=atan(e2/e1)+M_PI;
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
        eul[1]=(round(pol[0]*sin(pol[1])*100)/100+350);
        break;
    case 'v':
        eul[0]=round(pol[0]*cos(pol[1])*100)/100;
        eul[1]=(round(pol[0]*sin(pol[1])*100)/100);
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


void PhysicsCalc::radialCollison(double colPosEul[2],double colSpeed[2]){
    double colPosPol[2]={0};
    colPosEul[0]=colPosEul[0]+25;
    colPosEul[1]=colPosEul[1]+50;
    double colSpeedRT[2]={0};
    this->eulToPol(colPosEul,colPosPol,'p');
    double fi=colPosPol[1];
    qDebug() << fi;
    if (fi<=(M_PI/2)){
        colSpeedRT[0]=-abs(colSpeed[0]*sin(fi))+abs(colSpeed[1]*cos(fi));
    }
    if (fi<=(M_PI) && fi>(M_PI/2)){
        colSpeedRT[0]=abs(colSpeed[0]*sin(fi))+abs(colSpeed[1]*cos(fi));
    }
    if (fi<=(M_PI*1.5) && fi>M_PI){
        colSpeedRT[0]=abs(colSpeed[0]*sin(fi))-abs(colSpeed[1]*cos(fi));
    }
    if (fi<=(2*M_PI) && fi>(M_PI*1.5)){
        colSpeedRT[0]=-abs(colSpeed[0]*sin(fi))-abs(colSpeed[1]*cos(fi));
    }
    colSpeedRT[1]=-colSpeed[0]*cos(fi)-colSpeed[1]*sin(fi);

    qDebug() << colSpeedRT[0] << colSpeedRT[1];
    colSpeed[0]=-(colSpeedRT[0]*cos(fi))+(colSpeedRT[1]*sin(fi));
    colSpeed[1]=(colSpeedRT[0]*sin(fi))+(colSpeedRT[1]*cos(fi));
    qDebug() << colSpeed[0] << colSpeed[1];
    /*
    if(colPosPol[1]<=90){
        fi=colPosPol[1];
        colSpeedRT[0]=colSpeed[0]*cos(fi)+colSpeed[1]*sin(fi);
        colSpeedRT[1]=-colSpeed[0]*sin(fi)+colSpeed[1]*cos(fi);
        colSpeedRT[0]=colSpeedRT[0]*(-1);
        colSpeed[0]=(colSpeedRT[0]/cos(fi))-(colSpeedRT[1]/sin(fi));
        colSpeed[1]=(colSpeedRT[0]/cos(fi))+(colSpeedRT[1]/sin(fi));
    }
    if(colPosPol[1]<=180 && colPosPol[1]>90){
        fi=colPosPol[1]-M_PI*0.5;
        colSpeedRT[0]=-colSpeed[0]*cos(fi)+colSpeed[1]*sin(fi);
        colSpeedRT[1]=-colSpeed[0]*sin(fi)-colSpeed[1]*cos(fi);
        colSpeedRT[0]=colSpeedRT[0]*(-1);
        colSpeed[0]=-(colSpeedRT[0]/cos(fi))-(colSpeedRT[1]/sin(fi));
        colSpeed[1]=(colSpeedRT[0]/cos(fi))-(colSpeedRT[1]/sin(fi));
    }
    if(colPosPol[1]<=270 && colPosPol[1]>180){
        fi=colPosPol[1]-M_PI;
        colSpeedRT[0]=-colSpeed[0]*cos(fi)-colSpeed[1]*sin(fi);
        colSpeedRT[1]=+colSpeed[0]*sin(fi)-colSpeed[1]*cos(fi);
        colSpeedRT[0]=colSpeedRT[0]*(-1);
        colSpeed[0]=-(colSpeedRT[0]/cos(fi))+(colSpeedRT[1]/sin(fi));
        colSpeed[1]=-(colSpeedRT[0]/cos(fi))-(colSpeedRT[1]/sin(fi));
    }
    if(colPosPol[1]<360 && colPosPol[1]>270){
        fi=colPosPol[1]-M_PI*1.5;
        colSpeedRT[0]=colSpeed[0]*cos(fi)-colSpeed[1]*sin(fi);
        colSpeedRT[1]=colSpeed[0]*sin(fi)+colSpeed[1]*cos(fi);
        colSpeedRT[0]=colSpeedRT[0]*(-1);
        colSpeed[0]=(colSpeedRT[0]/cos(fi))+(colSpeedRT[1]/sin(fi));
        colSpeed[1]=-(colSpeedRT[0]/cos(fi))+(colSpeedRT[1]/sin(fi));
    }
    */
}
