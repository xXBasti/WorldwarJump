#include "physicscalc.h"
//#include <QtMath>
#include <cmath>
#include <QList>
#include "gameworld.h"
#include "terrain.h"
#include "battleunit.h"
#include "projectile.h"
#include "gamesettings.h"
#include <typeinfo>
#include <QDebug>


#include <stdlib.h>
#include <ctime>

#define M_PI 3.14159

PhysicsCalc::PhysicsCalc()
{
    counter = 0;
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

    double gravityVector[2];
    gravVec( worldObject , gravityVector);

    double gravAngleDiff = gravityAngleDifference(angular[0], gravityVector);
    if(gravAngleDiff > 180) gravAngleDiff = gravAngleDiff - 360;
    if(gravAngleDiff < -180) gravAngleDiff = gravAngleDiff + 360;

    if(worldObject->getChar() == 'p'){

        angular[1] = 0;
        double projectileSpeed[2] = {0};
        projectileSpeed[0] = worldObject->getSpeed()[0];
        projectileSpeed[1] = worldObject->getSpeed()[1];
        double polSpeed[2] = {0};
        eulToPol(projectileSpeed, polSpeed, 'v');
        double speedAngle = (polSpeed[1]*(180/M_PI));
        angular[0] = speedAngle;
        worldObject->setRotation(angular[0]);

    }else if(worldObject->getChar() == 'b'){
        worldObject->setRotation(angular[0] + timeStep*angular[1]);
        angular[0] = angular[0] + timeStep*angular[1];
        if(angular[0] > 360 || angular[0] < -360){
           angular[0] = (static_cast<double>((static_cast<int>(angular[0]))%360));
        }
        //! The stabilization module only activates when the object is close to the ground -Can
        //Stabilization module
        double distanceToGround = 400 - vectorsAbsoluteValue(gravityVector);
        int stabilizationFactor;
        int timeDecay;
        double maxRotVel = 7;
        if(distanceToGround < 200){
            stabilizationFactor = 80;
            timeDecay = 30;
            angular[1] =  exp(-(timeStep/timeDecay))*(angular[1] - (gravAngleDiff/stabilizationFactor));

            if(angular[1] < - maxRotVel){
                angular[1] = -maxRotVel;
            }else if(angular[1] > maxRotVel){
                angular[1] = maxRotVel;
            }

        }else if(distanceToGround < 300){
            stabilizationFactor = 70;
            timeDecay = 35;
            angular[1] =  exp(-(timeStep/timeDecay))*(angular[1] - (gravAngleDiff/stabilizationFactor));

            if(angular[1] < - maxRotVel){
                angular[1] = -maxRotVel;
            }else if(angular[1] > maxRotVel){
                angular[1] = maxRotVel;
            }

        }else{
            stabilizationFactor = 200;
            timeDecay = 80;
            angular[1] =  exp(-(timeStep/timeDecay))*(angular[1] - (gravAngleDiff/stabilizationFactor));
        }
    }
     counter = counter +1;
     if(counter == 200){
     //   qDebug() << "Angle difference: "<<gravAngleDiff ;
     //   qDebug() << "Angle velocity: " << angular[1];
        //double * point = {0};
        //getBottomLeft(worldObject,point);
        //qDebug() << "bottom left: " << QPointF(point[0],point[1]);
        //getBottomRight(worldObject,point);
        //qDebug() << "bottom right: " << QPointF(point[0],point[1]);
        //qDebug() << "Top left: " << worldObject->scenePos();
        //getTopLeft(worldObject,point);
        //qDebug() << "Top left: " << QPointF(point[0],point[1]);
        //getTopRight(worldObject, point);
        //qDebug() << "Top right: " << QPointF(point[0],point[1]);
/*        getImpactPoint(worldObject, point);
        qDebug() << "Furthest Point:" << QPointF(point[0],point[1]);*/
         if(worldObject->getChar() == 'p'){
             qDebug() << "Projectile:" << angular[0] << " : " << angular[1];
         }

         counter = 0 ;

 }

/*if(typeid(*worldObject) == typeid(Projectile)){
    return;
}*/
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
 * @brief PhysicsCalc::gravityVector gives the gravity vector
 * effecting an objects center of mass at a certain time.
 * First element gives the x and the second gives the y coordinate.
 * @param worldObject
 */
void PhysicsCalc::gravVec(WorldObject *worldObject, double *gravityVector)
{
    double x = worldObject->getCenterOfMass()[0];
    double y = worldObject->getCenterOfMass()[1];
    QPointF point(x,y);
    gravityVector[0] = worldObject->sceneTransform().map(point).x() - 400;
    gravityVector[1] = worldObject->sceneTransform().map(point).y() - 400;
}
/**
 * @brief PhysicsCalc::gravityAngleDifference calculates the angle
 * from the gravity vector to the current orientation.
 * The positive direction is clockwise.
 * @param rotation
 * @param gravityVector
 * @return
 */
double PhysicsCalc::gravityAngleDifference(double rotation, double *gravityVector)
{
    double gravityVectorAngle = atan2(gravityVector[1], gravityVector[0])*(180/M_PI) - 90;
    if(gravityVectorAngle < 0)  gravityVectorAngle += 360;
    if(rotation < 0) rotation += 360;
    return(rotation - gravityVectorAngle);

}

double PhysicsCalc::roundDown(double numberToRound, int digit)
{
    if(numberToRound >= 0){

        return(pow(10, -digit)*floor((pow(10, digit)*numberToRound)));

    }else{

        return(-pow(10, -digit)*floor((pow(10, digit)*abs(numberToRound))));
    }

}

void PhysicsCalc::getTopRight(WorldObject *worldObject, double * topRight)
{
    topRight[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().topRight())).x();
    topRight[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().topRight())).y();
}

void PhysicsCalc::getTopLeft(WorldObject *worldObject, double *topLeft)
{
    topLeft[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().topLeft())).x();
    topLeft[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().topLeft())).y();
}

void PhysicsCalc::getBottomRight(WorldObject *worldObject, double *bottomRight)
{

    bottomRight[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().bottomRight())).x();
    bottomRight[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().bottomRight())).y();
}

void PhysicsCalc::getBottomLeft(WorldObject *worldObject, double *bottomLeft)
{
    QPointF point = worldObject->sceneTransform().map(worldObject->boundingRect().bottomLeft());
    bottomLeft[0] = point.x();;
    bottomLeft[1] = point.y();;
}

void PhysicsCalc::getImpactPoint(WorldObject *worldObject, double *impactPoint)
{
    double ** cornerpoint;
    double * topRight = {0};
    getTopRight(worldObject, topRight);
    topRight[0] = topRight[0] - 400;
    topRight[1] = topRight[1] - 400;
    cornerpoint[0] = topRight;
    double * topLeft = {0};
    getTopRight(worldObject, topLeft);
    topLeft[0] = topLeft[0] - 400;
    topLeft[1] = topLeft[1] - 400;
    cornerpoint[1] = topLeft;
    double * bottomRight = {0};
    getTopRight(worldObject, bottomRight);
    bottomRight[0] = bottomRight[0] - 400;
    bottomRight[1] = bottomRight[1] - 400;
    cornerpoint[2] = bottomRight;
    double * bottomLeft = {0};
    getTopRight(worldObject, bottomLeft);
    bottomLeft[0] = bottomLeft[0] - 400;
    bottomLeft[1] = bottomLeft[1] - 400;
    cornerpoint[3] = bottomLeft;

    double abs = vectorsAbsoluteValue(cornerpoint[0]);
    double nextAbs;
    int biggest = 0;
    for(int i = 1; i < 4; i++){
         nextAbs = vectorsAbsoluteValue(cornerpoint[i]);
         if(abs < nextAbs){
             abs = nextAbs;
             biggest = i;
         }
    }

    impactPoint[0] = cornerpoint[biggest][0];
    impactPoint[1] = cornerpoint[biggest][1];

}

/**
* @brief PhysicsCalc::calculateNewValues calculates the next position of the given WorldObject
* based on it's current position and its current speed.
* Then it sets the object's new position and new speed
* When the WorldObject moves below the ground (collision) the movement speed of the WorldObject is inverted
* @param worldObject the WorldObject instance for which new position
*/
void PhysicsCalc::calculateNewValues(WorldObject* worldObject) {
    if (CollideWithTerrain(worldObject)){

        if(typeid(*worldObject)== typeid(Projectile)){
            worldObject->setHitCounter(worldObject->getHitCounter()+1);
            if(worldObject->getHitCounter()>=10){
                worldObject->~WorldObject();
                return;
            }
        }

        double * eulSpeed = worldObject->getSpeed();
        double eulPosition [2];
        worldObject->getPosition(eulPosition);
        double radialSpeed [2];
        // radialSpeed[0] is radial speed
        // radialSpeed[1] is tangential speed

        // transform from eulSpeed to radialSpeed
        velocityEulerToRadialCoordinates(eulPosition, eulSpeed, radialSpeed, true);
        // radial speed points to the center at collision
        radialSpeed[0] = -abs(radialSpeed[0]) -abs(0.15*radialSpeed[1]);
        //qDebug() << "radialSpeed: " << QString::number(radialSpeed[0]);
        radialSpeed[0] = roundDown(radialSpeed[0],1);
        //qDebug() << "radialSpeed: " << QString::number(radialSpeed[0]);
        // tangetial speed decreases at collision
        //radialSpeed[1] = 0.85*radialSpeed[1];
        // increase rotation at collision
         //worldObject->setRotVel(worldObject->getRotVel()-1*radialSpeed[1]); // Parameter: 1

        // transform from radialSpeed to eulSpeed
        velocityEulerToRadialCoordinates(eulPosition, radialSpeed, eulSpeed, false);
        //*worldObject->setSpeed(eulSpeed);

        // make object's rotation inverse and dampened at collision
        worldObject->setRotVel(worldObject->getRotVel()*-0.7);
    }
    if(CollideWithUnit(worldObject)!=NULL && typeid(*CollideWithUnit(worldObject))== typeid(BattleUnit) && typeid(*worldObject)== typeid(BattleUnit) ){
        WorldObject* wO=(WorldObject*)CollideWithUnit(worldObject);
        //impuls(wO,worldObject);
        inverseSpeed(worldObject,wO);
        meeleDamage(wO,worldObject);
    }
    // get object's speed and position
    double * speed = worldObject->getSpeed();
    double posCoordinates [2];
    posCoordinates[0] = worldObject->x();
    posCoordinates[1] = worldObject->y();

    // Euler
    worldObject->setPos(posCoordinates[0]+timeStep*speed[0],
                        posCoordinates[1]+timeStep*speed[1]);
    double radialSpeed [2];
    velocityEulerToRadialCoordinates(posCoordinates, speed, radialSpeed, true);
    radialSpeed[0] = radialSpeed[0]+gravity; //parameter
    velocityEulerToRadialCoordinates(posCoordinates, radialSpeed, speed, false);
    speed[0] = 0.98*speed[0]; //parameter
    speed[1] = 0.98*speed[1];

    // set new speed values
    //*worldObject->setSpeed(speed);
    return;
}


double PhysicsCalc::vectorsAbsoluteValue(double *vector)
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
    lVector[0] = eulInputPosition[0] - 375; //GameWorldSize && GameUnitSize
    lVector[1] = 375 - eulInputPosition[1];
    double vecLength = vectorsAbsoluteValue(lVector);
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
        e1=eul[0]-400; //350 später gamesize/2
        e2=(eul[1]-400); // damit polar kosi in der Mitte des Bildschirms ist.
        break;
    case 'v':
        e1=eul[0];
        e2=(eul[1]);
        break;
    case 'b':
        e1=eul[0]-400;
        e2=-(eul[1]-400);
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
        eul[0]=round(pol[0]*cos(pol[1])*100)/100+400;
        eul[1]=(round(pol[0]*sin(pol[1])*100)/100+400);
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

QGraphicsItem* PhysicsCalc::CollideWithUnit(WorldObject* object)
{
    QList<QGraphicsItem *> colliding_items = object->collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid(*(colliding_items[i]))== typeid(BattleUnit) || typeid(*(colliding_items[i]))== typeid(Projectile))
        {
            return (colliding_items[i]);
        }
    }
    return NULL;
}



void PhysicsCalc::radialCollison(double colPosEul[2],double colSpeed[2]){
    double colPosPol[2]={0};
    colPosEul[0]=colPosEul[0]+25;
    colPosEul[1]=colPosEul[1]+50;
    double colSpeedRT[2]={0};
    this->eulToPol(colPosEul,colPosPol,'p');
    double fi=colPosPol[1];
    //qDebug() << fi;
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

    //qDebug() << colSpeedRT[0] << colSpeedRT[1];
    colSpeed[0]=-(colSpeedRT[0]*cos(fi))+(colSpeedRT[1]*sin(fi));
    colSpeed[1]=(colSpeedRT[0]*sin(fi))+(colSpeedRT[1]*cos(fi));
    //qDebug() << colSpeed[0] << colSpeed[1];
}

void PhysicsCalc::hitUnit(WorldObject * worldObject) {
    //QGraphicsItem* I=this->CollideWithUnit(worldObject);
    WorldObject* I=(WorldObject*)this->CollideWithUnit(worldObject);
    if(!(I==NULL)){
        worldObject->setHitCounter(worldObject->getHitCounter()+1);
        bool frendlyFireCheck= (typeid(*I) == typeid(BattleUnit)) && worldObject->getPlayer()==I->getPlayer() && !settings->getFrendlyFire();
        if((worldObject->getHitCounter())>=4){
            impuls(I,worldObject);
            ((Projectile*)worldObject)->getshootingUnit()->setProjectile(((Projectile*)worldObject)->getshootingUnit()->getProjectile()+1);
            if(!frendlyFireCheck){
                I->setHealthpoints(I->getHealthpoints()-worldObject->getDamage());
                qDebug() <<worldObject->getDamage()<< "you have "<<I->getHealthpoints();
                checkHealth(I);
            }
            worldObject->~WorldObject();
        }
    }

}

void PhysicsCalc::checkHealth(WorldObject* obj){
    if (obj->getHealthpoints()<=0){
        if(obj->getPlayer()==player1){
            settings->setPlayer1UnitCount(settings->getPlayer1UnitCount()-1);
        }
        else{
            settings->setPlayer2UnitCount(settings->getPlayer2UnitCount()-1);
        }
        obj->~WorldObject();
            checkWinCondition();
    }

}

int PhysicsCalc::getPlayerone()
{
    return playerone;
}

int PhysicsCalc::getPlayertwo()
{
    return playertwo;
}

void PhysicsCalc::setPlayerone(int po)
{
    this->playerone=po;
}

void PhysicsCalc::setPlayertwo(int pt)
{
    this->playertwo=pt;
}


void PhysicsCalc::impuls(WorldObject* obj1,WorldObject* obj2){
    double* v1=obj1->getSpeed();
    double* v2=obj2->getSpeed();
    double v1s[2];
    double v2s[2];
    int m1=obj1->getWeight();
    int m2=obj2->getWeight();
    v1s[0]= v1[0];
    v1s[1]= v1[1];
    v2s[0]= v2[0];
    v2s[1]= v2[1];

    v1s[0]=((m1-m2)*v1[0]+2*m2*v2[0])/(m1+m2);
    v1s[1]=((m1-m2)*v1[1]+2*m2*v2[1])/(m1+m2);
    v2s[0]=((m2-m1)*v2[0]+2*m1*v1[0])/(m1+m2);
    v2s[1]=((m2-m1)*v2[1]+2*m1*v1[1])/(m1+m2);
    obj1->setSpeed(v1s);
    obj2->setSpeed(v2s);
}


void PhysicsCalc::checkWinCondition(){
    if(settings->getPlayer1UnitCount()<=-1){
        emit this->playeronewins();
        qDebug() <<"Player two wins";
    }
    if(settings->getPlayer2UnitCount()<=-1){
        qDebug() <<"Player one wins";
        emit this->playertwowins();
    }
}

void PhysicsCalc::inverseSpeed(WorldObject* colliding1,WorldObject* colliding2){
    double* v1=colliding1->getSpeed();
    double* v2=colliding2->getSpeed();
    v1[0]=v1[0]*-1;
    v1[1]=v1[1]*-1;
    v2[0]=v2[0]*1;
    v2[1]=v2[1]*1;
    colliding1->setSpeed(v1);
    colliding2->setSpeed(v2);
}

void PhysicsCalc::meeleDamage(WorldObject* colliding1,WorldObject* colliding2){
    //The slower Object gets the Damage
    double* v1=colliding1->getSpeed();
    double* v2=colliding2->getSpeed();

    if( (colliding1->getPlayer()!=colliding2->getPlayer())  ){
        if(vectorsAbsoluteValue(v2)-vectorsAbsoluteValue(v1)>10){
           colliding1->setHealthpoints(colliding1->getHealthpoints()-colliding2->getDamage());
           //qDebug() << "meele!"<<colliding2->getDamage()<< "you have "<<colliding1->getHealthpoints();
           checkHealth(colliding1);
        }
        if(vectorsAbsoluteValue(v1)-vectorsAbsoluteValue(v2)>10){
            colliding2->setHealthpoints(colliding2->getHealthpoints()-colliding1->getDamage());
            //qDebug() <<"meele!"<<colliding1->getDamage()<< "you have "<<colliding2->getHealthpoints();
            checkHealth(colliding2);
        }
    }
}

bool PhysicsCalc::collideWithAny(WorldObject* object){
    if(CollideWithTerrain(object)){
        return true;
    }
    if(CollideWithUnit(object)!=NULL){
        return true;
    }
    return false;
}

void PhysicsCalc::unitUnitCollisionFunc(BattleUnit* bat1,BattleUnit* bat2){
    double* c1=bat1->getCenterOfMass();
    double* c2=bat2->getCenterOfMass();
    double* s1=bat1->getSpeed();
    double* s2=bat2->getSpeed();
    double shd1[2]; //Speed in hit direction;
    double shd2[2];
    double vec[2];
    double dir[2];
    double angle1,angle2;
    vec[0]=c2[0]-c1[0];
    vec[1]=c2[1]-c1[1];
    dir[0]=vec[0]/vectorsAbsoluteValue(vec);
    dir[1]=vec[1]/vectorsAbsoluteValue(vec);
    angle1=atan(vec[0]/vec[1]);
    angle2=atan(vec[1]/vec[0]);
    shd1[0]=s1[0]*sin(angle1)+s1[1]*sin(angle2);
    shd1[1]=s1[0]*cos(angle1)+s1[1]*cos(angle2);




}
