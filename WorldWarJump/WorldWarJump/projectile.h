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

private:
    ProjectileType pT;
    int damage;
};

#endif // PROJECTILE_H
