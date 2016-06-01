#include "physicscalc.h"

PhysicsCalc::PhysicsCalc()
{

}

void PhysicsCalc::calculateNewValues(WorldObject * worldObject)
{
    worldObject->setPos(worldObject->x()+20, worldObject->y()+20);
}
