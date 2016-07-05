#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "input.h"
#include "gameworld.h"



/**
 * @brief Basic implementation of a physical object for other classes to inheriting from. -Tomas
 *
 * Detailed: functions like move(), jump() + basic physical attributes like speed, rot, orientation and more.
 */
class WorldObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT



    public:

        WorldObject(GameWorld *parentView, Player p, SoundPlayer *soundplayer);

        //for sound
        SoundPlayer *soundpointer;

        void setSpeed(double* newSpeed);
        void getPosition(double * outputPointer);
        double* getSpeed();
        GameWorld * parentView;

        //For orientation

        void setOrientation(double newOrientation);
        double  getOrientation() const;

        void setRotVel(double newRotVel);
        double getRotVel() const;

        //For orientation

        void setCenterOfMass(double * newCenterOfMass);
        double * getCenterOfMass();
        bool collidedBefore;
        void setHitCounter(int hit);
        int getHitCounter();
        ~WorldObject();

        Player getPlayer() const;
        int getWeight();
        void setWeight(int w);
        int getHealthpoints();
        int getDamage();
        void setDamage(int d);
        void setHealthpoints(int points);
        void setProjectile(int proj);
        int getProjectile();

        char getChar();

        bool getBounced() const;
        void setBounced(bool value);

        bool getFirstcollide() const;
        void setFirstcollide(bool col);

        bool okToJump;
        int jumpCounter;

        bool orientationChanged;
        int orientationChangeCount;
    protected:

        Player p;
        char ObjectType;
    private:



        double speed [2];
        void getNewValuesFromPhysicsCalc();
        int weigth;
        //For orientation
        //! Orientation and Angular Rotational Velocity of the objects -Can
        double orientation;
        double rotVel;
        //For orientation

        //! Center of mass to be the centerpoint of rotation and speed calculations -Can
        double centerOfMass[2];
        int damage;
        int hitcounter =0;
        int healthpoints;
        int projectilselector;
        bool bounced;
        bool firstcollide;


public slots:
        void move();
        void jump();
        void hit();
signals:
        void sendHealth(int health);
};

#endif // WORLDOBJECT_H
