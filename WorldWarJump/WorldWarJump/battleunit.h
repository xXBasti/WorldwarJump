#ifndef BATTLEUNIT_H
#define BATTLEUNIT_H
#include "worldobject.h"
#include <QObject>
class BattleUnit :public WorldObject
{
    Q_OBJECT
public:
    BattleUnit(GameWorld * parentView, Player p);
    double getFiredirection();
    void setFiredirection(double direction);
private:
    double firedirection;
    void setPicture();
public slots:
    void shoot();
};

#endif // BATTLEUNIT_H
