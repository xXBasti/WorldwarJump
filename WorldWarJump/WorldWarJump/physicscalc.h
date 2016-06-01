#ifndef PHYSICSCLAC_H
#define PHYSICSCLAC_H

#include "worldobject.h"

class PhysicsCalc
{
public:
    PhysicsCalc();

    int* eulToPol(int*);
    int* PolToEul(int*);

    void calculateNewValues(WorldObject *);
};

#endif // PHYSICSCLAC_H
