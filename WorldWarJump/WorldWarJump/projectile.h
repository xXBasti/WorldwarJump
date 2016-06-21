#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"

#include <QObject>

class Projectile : public WorldObject
{
    Q_OBJECT
public:
    Projectile(GameWorld *parentView,WorldObject *shootingUnit,ProjectileType p);
    void fly();

    ~Projectile();
    void recoil(WorldObject* obj1,WorldObject* obj2);
    //I needed to transport this //Wtf?
    void polToEul(double * pol, double* eul,char type);
    WorldObject *getshootingUnit();

private:
    WorldObject* shootingUnit;
    ProjectileType pT;
    int damage;
    void setPicture(Player p);
};

#endif // PROJECTILE_H
