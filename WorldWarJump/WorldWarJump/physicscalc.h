#ifndef PHYSICSCALC_H
#define PHYSICSCALC_H

#include "worldobject.h"
#include <QGraphicsItem>
#include "gameworld.h"

/*
 * eul[1] =x
 * eul[2] =y
 * pol[1] =r
 * pol[2] =fi
 */

class PhysicsCalc
{
public:
    PhysicsCalc();
    int* eulToPol(int*);
    int* PolToEul(int*);

    //Tomas
    void calculateNewValues(WorldObject *);
    // Std: gravity = 1; timeStep = 2;
    double gravity = 1;
    double timeStep = 2;
    //Tomas

    //Basti
    void eulToPol(double * eul, double* pol);
    void polToEul(double * pol, double* eul);
    //Basti

    //! CollideWithTerrain checks if one touches the ground and returns a boolean argument. - WANG
    bool CollideWithTerrain(WorldObject *);
};

#endif // PHYSICSCLAC_H
