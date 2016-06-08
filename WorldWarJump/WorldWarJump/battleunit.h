#ifndef BATTLEUNIT_H
#define BATTLEUNIT_H
#include "worldobject.h"

class BattleUnit :public WorldObject
{
public:
    BattleUnit(GameWorld * parentView,Player p);
    void shoot();
    double getFiredirection();
    void setFiredirection(double direction);
private:
    double firedirection;

};

#endif // BATTLEUNIT_H
