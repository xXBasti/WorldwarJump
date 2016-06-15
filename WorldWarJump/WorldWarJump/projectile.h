#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"

#include <QObject>

class Projectile : public WorldObject
{
    Q_OBJECT
public:
    Projectile(GameWorld *parentView,int x,int y,double dir,ProjectileType p);
    void fly();

    ~Projectile();

    Projectile(GameWorld *parentView, WorldObject *shootingUnit);
private:
    ProjectileType pT;
    int damage;
    void setPicture(Player p);
};

#endif // PROJECTILE_H
