#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"
#include "gameworld.h"

class WorldObject : public QObject, public QGraphicsRectItem {
    Q_OBJECT



    public:

        WorldObject(GameWorld *parentView);
        void setSpeed(double* newSpeed);
        double* getSpeed();
        GameWorld * parentView;

        //For orientation

        void setOrientation(double newOrientation);
        double  getOrientation() const;

        void setRotVel(double newRotVel);
        double getRotVel() const;
        //For orientation

    private:

        double speed [2];
        void getNewValuesFromPhysicsCalc();
        int weigth;

        //For orientation
        //! Orientation and Angular Rotational Velocity of the objects -Can
        double orientation;
        double rotVel;
        //For orientation

    public slots:

        void move();
        void jump();

};

#endif // WORLDOBJECT_H
