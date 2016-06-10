#ifndef BATTLEUNIT_H
#define BATTLEUNIT_H
#include "worldobject.h"

class BattleUnit :public WorldObject
{
public:
    BattleUnit(GameWorld * parentView,Player p);
    double getFiredirection();
    void setFiredirection(double direction);
private:
    double firedirection;
public slots:
    void shoot();
};

#endif // BATTLEUNIT_H
