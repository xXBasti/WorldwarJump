#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"
#include "soundplayer.h"
#include "battleunit.h"
#include <QObject>

class Projectile : public WorldObject
{
    Q_OBJECT
public:

    Projectile(GameWorld *parentView, BattleUnit *shootingUnit, ProjectileType p, SoundPlayer *soundplayer, double *shootingPoint);

    ~Projectile();
    //Basti
    void recoil(WorldObject* obj1,WorldObject* obj2);
    //Basti
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
