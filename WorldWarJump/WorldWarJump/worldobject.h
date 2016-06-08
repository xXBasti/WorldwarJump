#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"
#include "gameworld.h"


enum projectileType {missile, balistic, ray, scrap};

class WorldObject : public QObject, public QGraphicsRectItem {
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

    private:

        double speed [2];
        void getNewValuesFromPhysicsCalc();
        int weigth;

        //For orientation
        //! Orientation and Angular Rotational Velocity of the objects -Can
        double orientation;
        double rotVel;
        //For orientation

        int healthpoints;
    public slots:

        void move();
        void jump();

};

#endif // WORLDOBJECT_H
