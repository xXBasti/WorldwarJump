#include "GameplayInterface.h"
#include <QDebug>
#include "physicscalc.h"

GameplayInterface::GameplayInterface()
{
    physicsCalulator = new PhysicsCalc();
}

