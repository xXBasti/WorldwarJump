#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"



class Projectile : public WorldObject
{
public:
    Projectile(GameWorld *parentView,int x,int y,double dir,projectileType pT);
    void fly();
    void hit();
    ~Projectile();
private:
    enum projectileType pT;
    int damage;

};

#endif // PROJECTILE_H
