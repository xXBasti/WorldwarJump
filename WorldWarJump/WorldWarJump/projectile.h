#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"



class Projectile : public WorldObject
{
public:
    Projectile(GameWorld *parentView,int x,int y,projectileType pT);
    void fly();
    void hit();
private:
    enum projectileType pT;
    int damage;

};

#endif // PROJECTILE_H
