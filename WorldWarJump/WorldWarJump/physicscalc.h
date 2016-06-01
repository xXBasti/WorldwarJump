#ifndef PHYSICSCLAC_H
#define PHYSICSCLAC_H

#include "worldobject.h"

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
};

#endif // PHYSICSCLAC_H
