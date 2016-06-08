#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "input.h"
#include "gameworld.h"

<<<<<<< HEAD
class WorldObject : public QObject, public QGraphicsPixmapItem {
=======
enum Player {player1, player2};
enum projectileType {missile, balistic, ray, scrap};

class WorldObject : public QObject, public QGraphicsRectItem {
>>>>>>> 26efc100a513ee8df2af4e2c99c7de1d4d94a3ca
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
