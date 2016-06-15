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
private:
    ProjectileType pT;
    int damage;
    void setPicture(Player p, ProjectileType pT);
};

#endif // PROJECTILE_H
