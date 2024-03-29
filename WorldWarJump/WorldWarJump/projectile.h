#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "worldobject.h"
#include "soundplayer.h"
#include "battleunit.h"
#include <QObject>

/**
 * @brief are shot by BattleUnit and have different types. - Basti and Can
 *
 * Detailed: types include missile, ballistic and ray, and their QGraphicPixmapItem, velocity and damage is dependant on this.
 */
class Projectile : public WorldObject
{
    Q_OBJECT
public:

    Projectile(GameWorld *parentView, BattleUnit *shootingUnit, ProjectileType p, SoundPlayer *soundplayer, double *shootingPoint);

    ~Projectile();
    //Basti
    void recoil(WorldObject* obj1,WorldObject* obj2);
    //Basti
    //!Due to unknown issues, this had to be copied here from physics calculator
    void polToEul(double * pol, double* eul,char type);
    WorldObject *getshootingUnit();



    private:
    WorldObject* shootingUnit;
    ProjectileType pT;
    int damage;
    void setPicture(Player p);

};

#endif // PROJECTILE_H
