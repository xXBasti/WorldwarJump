#ifndef PHYSICSCALC_H
#define PHYSICSCALC_H

#include <QObject>

#include "worldobject.h"
#include <QGraphicsItem>
#include "gameworld.h"
#include "gamesettings.h"
#include "battleunit.h"

class PhysicsCalc : public QObject
{
Q_OBJECT
public:
    PhysicsCalc();

    //Can
    //Orientation
    void calculateNewRotValues(WorldObject * worldObject);
    void updateRotValues(WorldObject * worldObject, double * angular);
    //Gravity vector
    void gravVec(WorldObject * worldObject, double * gravityVector);
    //Bounding rectangle coordinates
    void getTopRight(WorldObject * worldObject, double * topRight);
    void getTopLeft(WorldObject * worldObject, double *topLeft);
    void getBottomRight(WorldObject * worldObject, double * bottomRight);
    void getBottomLeft(WorldObject * worldObject, double *bottomLeft);
    //Find the closest rectangle corner to the ground
    void getImpactPoint(WorldObject * worldObject, double *impactPoint);
    //Clockwise Rotation angle difference to the inverse of gravity vector
    double gravityAngleDifference(double rotation, double * gravityVector);
    int counter;
    //Gives the rounded down number after a certain digit
    double roundDown(double numberToRound, int digit);
    //Can

    //Tomas
    void calculateNewValues(WorldObject *);
    double vectorsAbsoluteValue(double * vector);
    GameSettings * settings;
    double gravity = settings->getGravity();
    double timeStep = settings->getTimeStep();
    void velocityEulerToRadialCoordinates(double * eulInputPosition, double * inputVelVector, double * outputVelVector, bool eulerToRadial);
    //Tomas

    //Basti
    void eulToPol(double * eul, double* pol,char type);
    void polToEul(double * pol, double* eul,char type);
    void radialCollison(double colPosEul[2],double colSpeedRT[2]);
    QGraphicsItem *CollideWithUnit(WorldObject *object);
    void hitUnit(WorldObject *worldObject);
    void impuls(WorldObject *obj1, WorldObject *obj2);
    void checkHealth(WorldObject *obj);
    int getPlayerone();
    int getPlayertwo();
    void setPlayerone(int po);
    void setPlayertwo(int pt);
    void checkWinCondition();
    void inverseSpeed(WorldObject *colliding1, WorldObject *colliding2);
    void meeleDamage(WorldObject *colliding1, WorldObject *colliding2);
    bool collideWithAny(WorldObject *object);
    void unitUnitCollisionFunc(BattleUnit *bat1, BattleUnit *bat2);
    //Basti

    //! CollideWithTerrain checks if one touches the ground and returns a boolean argument. - WANG
    bool CollideWithTerrain(WorldObject* object);


signals:
    void playeronewins();
    void playertwowins();

private:
    int playerone;
    int playertwo;

};

#endif // PHYSICSCLAC_H
