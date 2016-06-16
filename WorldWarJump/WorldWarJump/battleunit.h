#ifndef BATTLEUNIT_H
#define BATTLEUNIT_H
#include "worldobject.h"
#include <QObject>
class BattleUnit :public WorldObject
{
    Q_OBJECT
public:
    BattleUnit(GameWorld * parentView, Player p,unitType unittype);
    BattleUnit(Player p,unitType unitType);
    double getFiredirection();
    void setFiredirection(double direction);
    unitType getUnittype();
private:
    double firedirection;
    void setPicture();
    unitType ut;
public slots:
    void shoot();
};

#endif // BATTLEUNIT_H
