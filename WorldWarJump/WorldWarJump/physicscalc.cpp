#include "physicscalc.h"

#include <cmath>
#include <QList>
#include <cmath>
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

/**
 * @brief PhysicsCalc::PhysicsCalc. JumpFrameLimit determines how many timesteps the unit
 * is allowed to not collide with the ground before it is able to jump again.
 * @param soundplayer the global soundplayer pointer
 */
PhysicsCalc::PhysicsCalc(SoundPlayer *soundplayer)
{
    JumpFrameLimit = 10;
    soundpointer = soundplayer;
    //Merge the number of units
    settings->setPlayer1UnitCount(settings->getPlayerRedShipCount()+settings->getPlayerRedTankCount());
    settings->setPlayer2UnitCount(settings->getPlayerBlueShipCount()+settings->getPlayerBlueTankCount());
}

/**
* @brief PhysicsCalc::calculateNewRotValues calculates the next orientation of the given WorldObject
* based on it's current orientation and its current angular velocity.
* Angular array stores in the following order, the angle and angular velocity.
* Different calculations on projectiles and battleunits.
* The projectiles "head" is made to always point the speed vector.
* The Battleunits are made to slowly stand perpendicular to the gravity vector in stabilization module.
* The closer they get to the center, the less they are stabilized.
* @param worldObject the worldobject to be calculated
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
            maxRotVel = 7;
            if(angular[1] < - maxRotVel){
                angular[1] = -maxRotVel;
            }else if(angular[1] > maxRotVel){
                angular[1] = maxRotVel;
            }

        }else if(distanceToGround < 300){
            stabilizationFactor = 70;
            timeDecay = 35;
            angular[1] =  exp(-(timeStep/timeDecay))*(angular[1] - (gravAngleDiff/stabilizationFactor));
            maxRotVel = 5;
            if(angular[1] < - maxRotVel){
                angular[1] = -maxRotVel;
            }else if(angular[1] > maxRotVel){
                angular[1] = maxRotVel;
            }

        }else{
            stabilizationFactor = 200;
            timeDecay = 80;
            angular[1] =  exp(-(timeStep/timeDecay))*(angular[1] - (gravAngleDiff/stabilizationFactor));
            maxRotVel = 4;
            if(angular[1] < - maxRotVel){
                angular[1] = -maxRotVel;
            }else if(angular[1] > maxRotVel){
                angular[1] = maxRotVel;
            }
        }
    }

    updateRotValues(worldObject, angular);
}
/**
 * @brief PhysicsCalc::updateRotValues sets the objects new orientation and new angular velocity
 * @param worldObject the worldobject to be updated
 * @param angular the angle and angular speed to be set
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
 * @param rotation the rotation of the unit
 * @param gravityVector the gravity vector of the unit
 * @return the difference between the units bottom and the gravity vector
 */
double PhysicsCalc::gravityAngleDifference(double rotation, double *gravityVector)
{
    double gravityVectorAngle = atan2(gravityVector[1], gravityVector[0])*(180/M_PI) - 90;
    if(gravityVectorAngle < 0)  gravityVectorAngle += 360;
    if(rotation < 0) rotation += 360;
    return(rotation - gravityVectorAngle);

}

/**
 * @brief PhysicsCalc::roundDown calculates the floor of a number from the given digit
 * @param numberToRound the number to be rounded down
 * @param digit the digit after which will be set to zero
 * @return the rounded number
 */
double PhysicsCalc::roundDown(double numberToRound, int digit)
{
    if(numberToRound >= 0){

        return(pow(10, -digit)*floor((pow(10, digit)*numberToRound)));

    }else{

        return(-pow(10, -digit)*floor((pow(10, digit)*abs(numberToRound))));
    }

}
/**
 * @brief PhysicsCalc::getTopRight calculates the top right point of the objects bounding rectangle in scene coordinates
 * @param worldObject
 * @param topRight the point position
 */
void PhysicsCalc::getTopRight(WorldObject *worldObject, double * topRight)
{
    topRight[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().topRight())).x();
    topRight[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().topRight())).y();
}
/**
 * @brief PhysicsCalc::getTopLeft calculates the top left point of the objects bounding rectangle in scene coordinates
 * @param worldObject
 * @param topLeft the point position
 */
void PhysicsCalc::getTopLeft(WorldObject *worldObject, double *topLeft)
{
    topLeft[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().topLeft())).x();
    topLeft[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().topLeft())).y();
}
/**
 * @brief PhysicsCalc::getBottomRight calculates the bottom right point of the objects bounding rectangle in scene coordinates
 * @param worldObject
 * @param bottomRight the point position
 */
void PhysicsCalc::getBottomRight(WorldObject *worldObject, double *bottomRight)
{

    bottomRight[0] = (worldObject->sceneTransform().map(worldObject->boundingRect().bottomRight())).x();
    bottomRight[1] = (worldObject->sceneTransform().map(worldObject->boundingRect().bottomRight())).y();
}
/**
 * @brief PhysicsCalc::getBottomLeft calculates the bottom left point of the objects bounding rectangle in scene coordinates
 * @param worldObject
 * @param bottomLeft the point position
 */
void PhysicsCalc::getBottomLeft(WorldObject *worldObject, double *bottomLeft)
{
    QPointF point = worldObject->sceneTransform().map(worldObject->boundingRect().bottomLeft());
    bottomLeft[0] = point.x();;
    bottomLeft[1] = point.y();;
}

/**
 * @brief PhysicsCalc::getImpactPoint
 * calculates the impact point with the cornerpoints of the given WorldObject.
 * @param worldObject the object, which impact point should be calculated.
 * @param impactPoint is pointer to the array where the point will be saved.
 */
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
*
* When the WorldObject moves below the ground (collision) the movement speed of the WorldObject
* in radial direction is set in the direction of the center.
* Then it sets the object's new position and new speed. -Tomas
*
* @param worldObject the WorldObject instance for which new position is to be calculated and set. If it is a WorldObject of the type Projectile
* ,then the Projectile bounce counter is increased.
*/
void PhysicsCalc::calculateNewValues(WorldObject* worldObject) {
    if (CollideWithTerrain(worldObject)){

        if(typeid(*worldObject)== typeid(Projectile)){
            //Change projectile transformation point to center with first collision
            if(worldObject->orientationChanged == false){
                worldObject->setTransformOriginPoint((worldObject->pixmap().width())/2,(worldObject->pixmap().height())/2);
                worldObject->orientationChanged = true;
            }
            //Count number of bounces a projectile has and if it is above the threashold destroy it
            if(worldObject->getBounced() == 0){
                worldObject->setBounced(1);
                worldObject->setHitCounter(worldObject->getHitCounter()+1);
                if(worldObject->getHitCounter() >= bounceB4Destruction){
                    worldObject->~WorldObject();
                    return;
                }
            }
        }
        worldObject->jumpCounter = 0;
        worldObject->okToJump = true;

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
        radialSpeed[0] = roundDown(0.70*radialSpeed[0],1);
        // tangetial speed decreases at collision
        radialSpeed[1] = 0.85*radialSpeed[1];
        // increase rotation at collision

        // transform from radialSpeed to eulSpeed
        velocityEulerToRadialCoordinates(eulPosition, radialSpeed, eulSpeed, false);


        // make object's rotation inverse and dampened at collision
        worldObject->setRotVel(roundDown(worldObject->getRotVel()*-0.7,0));
    }else{
        worldObject->setBounced(0);
        worldObject->jumpCounter ++;
        if(worldObject->jumpCounter >= JumpFrameLimit){
            worldObject->okToJump = false;
            worldObject->jumpCounter = JumpFrameLimit;
        }
    }

    if(CollideWithUnit(worldObject)!=NULL && typeid(*CollideWithUnit(worldObject))== typeid(BattleUnit) && typeid(*worldObject)== typeid(BattleUnit)){
        WorldObject* wO=(WorldObject*)CollideWithUnit(worldObject);
        if( settings->getUnitcollison() ){
        //impuls(wO,worldObject);
        //inverseSpeed(worldObject,wO);
        this->unitUnitCollisionFunc(worldObject,wO);
        }
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
    worldObject->setSpeed(speed);
    return;
}

/**
 * @brief PhysicsCalc::vectorsAbsoluteValue calculates the absolute value for a vector in R².
 * @param vector
 * @return absolute value of a vector in R².
 */
double PhysicsCalc::vectorsAbsoluteValue(double *vector)
{
    return sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
}

/**
 * @brief PhysicsCalc::velocityEulerToRadialCoordinates transforms the velocity of a WorldObject. -Tomas
 *
 * Detailed: the new velocity vector is in a coordinate system which always points with the first coordinate from the center
 * of the world through the position of the unit outwards radially. The second coordinate points facing int the same direction to the left.
 *
 * @param eulInputPosition objects position to determine what direction is outward.
 * @param eulInputVelocity objects velocity to transform
 * @param radialOutput first coordinate radial, second coordinate is tangential to the Terrain 's circle.
 * @param eulerToRadial true if transforming from Euler coordinates, or false if transforming back to Euler coordinates.
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
 * translates the given cartesian coordinate system
 * to a polar coordinate system and saves them into a given output pointer.
 * @param eul inputpointer in cartesian coordinates, [0] -> x, [1] -> y.
 * @param pol outputpointer in polar coordinates, [0] -> r, [1] -> phi.
 * @param type type of the translation, v -> velocity, p -> position
 */

void PhysicsCalc::eulToPol(double * eul, double* pol,char type){
    double e1;
    double e2;
    switch(type){
    case 'p':
        e1=eul[0]-400;
        e2=(eul[1]-400);
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
 * This function transforms polar coordinates into cartesian coordinates.
 * @param pol is the inputpointer for polar coordinates, [0] -> x, [1] -> y.
 * @param eul is the outputpointer for the cartesian coordinates, [0] -> r, [1] -> phi.
 * @param type type of the translation, v -> velocity, p -> position.
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

/**
 * @brief PhysicsCalc::CollideWithTerrain
 * checks if the given object collides with the terrain and returns true or false.
 * @param object is the WorldObject, which will be checked.
 * @return true if it collides, false if it does not.
 */
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
/**
 * @brief PhysicsCalc::CollideWithUnit
 * checks, if an object collides with an other object of the type
 * BattleUnit or Projectile and returns that object.
 * @param object is the object, which will be checked.
 * @return is a pointer to the object, the object collides with
 */
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


/**
 * @brief PhysicsCalc::hitUnit
 * calculates the damage, between two colliding objects and
 * checks one of the WorldObject gets destroyed.
 * @param worldObject is the WorldObject for which the collision will be calculated.
 */
void PhysicsCalc::hitUnit(WorldObject * worldObject) {
    WorldObject* I=(WorldObject*)this->CollideWithUnit(worldObject);
    if(!(I==NULL)){
        worldObject->setHitCounter(worldObject->getHitCounter()+1);
        bool frendlyFireCheck= (typeid(*I) == typeid(BattleUnit)) && worldObject->getPlayer()==I->getPlayer() && !settings->getFrendlyFire();
        if((worldObject->getHitCounter())>=2){
            impuls(I,worldObject);
            soundpointer->playHit();
            if(typeid(*I) == typeid(BattleUnit))
                ((Projectile*)worldObject)->getshootingUnit()->setProjectile(((Projectile*)worldObject)->getshootingUnit()->getProjectile()+1);
            if(!frendlyFireCheck){
                I->setHealthpoints(I->getHealthpoints()-worldObject->getDamage());
                checkHealth(I);
            }
            worldObject->~WorldObject();
        }
    }

}

/**
 * @brief PhysicsCalc::checkHealth
 * checks if the given object has healtpoint lower or eqaul to zero and destroyes that unit.
 * The unitcounter of the owining player will be decreased too.
 * @param obj is the WorldObject whicht should be checked
 */
void PhysicsCalc::checkHealth(WorldObject* obj){
    if (obj->getHealthpoints()<=0){
        if(obj->getPlayer()==player1){
            // Only decrease if the WorldObject is a BattleUnit
            if(typeid(*obj) == typeid(BattleUnit))
                settings->setPlayer1UnitCount(settings->getPlayer1UnitCount()-1);
        }
        else{
            // Only decrease if the WorldObject is a BattleUnit
            if(typeid(*obj) == typeid(BattleUnit))
                settings->setPlayer2UnitCount(settings->getPlayer2UnitCount()-1);
        }
        obj->~WorldObject();
        checkWinCondition();
    }

}

/**
 * @brief PhysicsCalc::impuls
 * excecutes the conservation of the linear momentum for
 * the two colliding objects obj1 and obj2.
 * @param obj1 is the first object which collides.
 * @param obj2 is the secound object which collides.
 */
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

/**
 * @brief PhysicsCalc::checkWinCondition
 * checks if one of the playes are out of units
 * and than emit a winning signal.
 */
void PhysicsCalc::checkWinCondition(){
    if(settings->getPlayer1UnitCount()<=0){
        emit this->playeronewins();
        qDebug() <<"Player two wins";
    }
    if(settings->getPlayer2UnitCount()<=0){
        qDebug() <<"Player one wins";
        emit this->playertwowins();
    }
}
/**
 * @brief PhysicsCalc::inverseSpeed
 * invertes the speed of the first given Worldobject.
 * @param colliding1 is the first WorldObject which speed gets inverted.
 * @param colliding2 is the secound WorldObject, which speed remains unchanged.
 */
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

/**
 * @brief PhysicsCalc::meeleDamage
 * calculates the Meele Damage between two Objects.
 * The unit which has a 10 values higher speed than the other deals the damage.
 * @param colliding1 is the first colliding object.
 * @param colliding2 is the secound colliding object.
 */
void PhysicsCalc::meeleDamage(WorldObject* colliding1,WorldObject* colliding2){
    //The slower Object gets the Damage
    double* v1=colliding1->getSpeed();
    double* v2=colliding2->getSpeed();

    if( (colliding1->getPlayer()!=colliding2->getPlayer())  ){
        if(vectorsAbsoluteValue(v2)-vectorsAbsoluteValue(v1)>2){
           colliding1->setHealthpoints(colliding1->getHealthpoints()-colliding2->getDamage());
           impuls(colliding1,colliding2);
           checkHealth(colliding1);
           emit meeleDmg();
        }
        if(vectorsAbsoluteValue(v1)-vectorsAbsoluteValue(v2)>2){
            colliding2->setHealthpoints(colliding2->getHealthpoints()-colliding1->getDamage());
            impuls(colliding1,colliding2);
            checkHealth(colliding2);
            emit meeleDmg();
        }

    }
}

/**
 * @brief PhysicsCalc::collideWithAny
 * checks it the given object collides with either an unit or the terrain.
 * @param object is the object, which will checked.
 * @return true if it collides, false if it do not.
 */
bool PhysicsCalc::collideWithAny(WorldObject* object){
    if(CollideWithTerrain(object)){
        return true;
    }
    if(CollideWithUnit(object)!=NULL){
        return true;
    }
    return false;
}

/**
 * @brief PhysicsCalc::unitUnitCollisionFunc
 * calculates the collision between two objects and
 * chanches the speed of the units. This function is called with BattleUnits.
 * @param bat1 is the first WorldObject which collides.
 * @param bat2 is the secound WorldObject which collides.
 */
void PhysicsCalc::unitUnitCollisionFunc(WorldObject* bat1,WorldObject* bat2){
    double c1[2];
    bat1->getPosition(c1);
    double c2[2];
    bat2->getPosition(c2);
    double* s1=bat1->getSpeed();
    double* s2=bat2->getSpeed();
    double shd1[2]; //Speed in hit direction;
    double shd2[2];
    double speed1pol[2];
    double vec[2];
    double vechd[2];
    double dir[2];
    double angle1,angle2;
    vec[0]=c2[0]-c1[0];
    vec[1]=c2[1]-c1[1];
    qDebug() <<vec[0]<<vec[1];
    dir[0]=vec[0]/vectorsAbsoluteValue(vec);
    dir[1]=vec[1]/vectorsAbsoluteValue(vec);
    angle1=atan(vec[0]/vec[1]);
    eulToPol(vec,speed1pol,'v');
    angle1=speed1pol[1];
    qDebug() <<angle1;
    vechd[0]=vec[0]*sin(angle1)+vec[1]*cos(angle1); //Sin und cos vertauschen?
    vechd[1]=vec[0]*cos(angle1)+vec[1]*sin(angle1);
    shd1[0]=s1[0]*cos(angle1)+s1[1]*sin(angle1);
    shd1[1]=s1[0]*sin(angle1)+s1[1]*cos(angle1);
    shd2[0]=s2[0]*cos(angle1)+s2[1]*sin(angle1);
    shd2[1]=s2[0]*sin(angle1)+s2[1]*cos(angle1);
    if(vechd[0]!=0){
        shd1[0]=sqrt(shd1[0]*shd1[0]+1)*-(vechd[0]/(sqrt(vechd[0]*vechd[0])));
        shd2[0]=sqrt(shd2[0]*shd2[0]+1)*(vechd[0]/(sqrt(vechd[0]*vechd[0])));
    }
    s1[0]=cos(angle1)*shd1[0]+sin(angle1)*shd1[1];
    s1[1]=sin(angle1)*shd1[0]-cos(angle1)*shd1[1];
    s2[0]=cos(angle1)*shd1[0]+sin(angle1)*shd1[1];
    s2[1]=sin(angle1)*shd1[0]-cos(angle1)*shd1[1];
    bat1->setSpeed(s1);
    bat2->setSpeed(s2);
}
