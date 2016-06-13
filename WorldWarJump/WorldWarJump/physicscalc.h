#ifndef PHYSICSCALC_H
#define PHYSICSCALC_H

#include "worldobject.h"
#include <QGraphicsItem>
#include "gameworld.h"

class PhysicsCalc
{
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
    //Clockwise Rotation angle difference to the inverse of gravity vector
    double gravityAngleDifference(double rotation, double * gravityVector);
    int counter;
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

};

#endif // PHYSICSCLAC_H
