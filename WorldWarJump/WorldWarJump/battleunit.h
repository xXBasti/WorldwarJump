#ifndef BATTLEUNIT_H
#define BATTLEUNIT_H
#include "worldobject.h"
#include "gamesettings.h"
#include <QObject>
#include <QTimer>

/**
 * @brief The BattleUnit class is a subclass of WorldObject and represents the player's fighting units on the field. - Basti
 */
class BattleUnit :public WorldObject
{
    Q_OBJECT
public:
    BattleUnit(GameWorld * parentView, Player player, SoundPlayer *soundplayer, unitType unittype);
    SoundPlayer *soundpointer;
    double getFiredirection();
    void setFiredirection(double direction);
    unitType getUnittype();
    void calculateShootingPoint(double *Point);
private:
    double firedirection;
    void setPicture();
    unitType ut;
    bool ableToShoot;
    QTimer* shootTimer;
public slots:
    void shoot();
    void setShootAble();
};

#endif // BATTLEUNIT_H
