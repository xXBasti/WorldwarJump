#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "input.h"
#include "gameworld.h"




class WorldObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT



    public:

        WorldObject(GameWorld *parentView, Player p);
        WorldObject(Player p);
        void setSpeed(double* newSpeed);
        void getPosition(double * outputPointer);
        double* getSpeed();
        GameWorld * parentView;

        //For orientation

        void setOrientation(double newOrientation);
        double  getOrientation() const;

        void setRotVel(double newRotVel);
        double getRotVel() const;

        void getTopRight(double * topRight);
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

        char getChar();
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

    public slots:
        void move();
        void jump();
        void hit();

};

#endif // WORLDOBJECT_H
