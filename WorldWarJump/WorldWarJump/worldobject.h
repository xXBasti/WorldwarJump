#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "input.h"
#include "gameworld.h"




class WorldObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT



    public:

        WorldObject(GameWorld *parentView);
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
        bool collidedBefore;
        void setHitCounter(int hit);
        int getHitCounter();
        int getWeight();
        void setWeight(int w);
        ~WorldObject();

        void setHealthpoints(int points);
        int getHealthpoints();
        int getDamage();
        Player getPlayer();
private:

        double speed [2];
        void getNewValuesFromPhysicsCalc();
        int weigth;

        //For orientation
        //! Orientation and Angular Rotational Velocity of the objects -Can
        double orientation;
        double rotVel;
        //For orientation
        int hitcounter =0;
        int healthpoints;
protected:
        int damage;
        Player pl;
    public slots:
        void move();
        void jump();
        void hit();

};

#endif // WORLDOBJECT_H
