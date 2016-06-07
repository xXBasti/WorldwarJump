#ifndef PHYSICSCALC_H
#define PHYSICSCALC_H

#include "worldobject.h"
#include <QGraphicsItem>
#include "gameworld.h"

/*
 * eul[0] =x
 * eul[1] =y
 * pol[0] =r
 * pol[1] =phi
 */

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
    double vectorsAbsoluteValue(double* vector);
    // Std: gravity = 1; timeStep = 2;
    double gravity = 0.001;
    double timeStep = 2;
    //Tomas

    //Basti
    void eulToPol(double * eul, double* pol,char type);
    void polToEul(double * pol, double* eul,char type);
    //Basti

    //! CollideWithTerrain checks if one touches the ground and returns a boolean argument. - WANG
    bool CollideWithTerrain(WorldObject* object);
    void radialCollison(double colPosEul[2],double colSpeedRT[2]);
};

#endif // PHYSICSCLAC_H
