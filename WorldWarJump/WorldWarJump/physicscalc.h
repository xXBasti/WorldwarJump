#ifndef PHYSICSCALC_H
#define PHYSICSCALC_H

#include "worldobject.h"
#include <QGraphicsItem>
#include "gameworld.h"
#include "gamesettings.h"

class PhysicsCalc
{

public:
    PhysicsCalc();

    //Can
    void calculateNewRotValues(WorldObject * worldObject);
    void updateRotValues(WorldObject * worldObject, double * angular);


    //Can

    //Tomas
    void calculateNewValues(WorldObject *);

    double vectorsAbsoluteValue(double * vector);

    // Std: gravity = 1; timeStep = 2;
    double gravity = 1;
    double timeStep = 2;
    void velocityEulerToRadialCoordinates(double * eulInputPosition, double * inputVelVector, double * outputVelVector, bool eulerToRadial);
    //Tomas

    //Basti
    void eulToPol(double * eul, double* pol,char type);
    void polToEul(double * pol, double* eul,char type);
    void radialCollison(double colPosEul[2],double colSpeedRT[2]);
    //Basti

    //! CollideWithTerrain checks if one touches the ground and returns a boolean argument. - WANG
    bool CollideWithTerrain(WorldObject* object);

    QGraphicsItem *CollideWithUnit(WorldObject *object);
    void hitUnit(WorldObject *worldObject);
    void impuls(WorldObject *obj1, WorldObject *obj2);
    void checkHealth(WorldObject *obj);
    void unitcheck();
private:
    GameWorld gw;
};

#endif // PHYSICSCLAC_H
