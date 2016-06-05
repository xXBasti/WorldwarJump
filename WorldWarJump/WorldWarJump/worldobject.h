#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"

class WorldObject : public QObject, public QGraphicsRectItem {
    Q_OBJECT

    public:

        WorldObject(Input* passInput);

        //For orientation

        void setOrientation(double newOrientation);
        double  getOrientation() const;

        void setRotVel(double newRotVel);
        double getRotVel() const;
        //For orientation

    private:

        Input *input;
        int weigth;

        //For orientation
        //! Orientation and Angular Rotational Velocity of the objects -Can
        double orientation;
        double rotVel;
        //For orientation

    public slots:

        void move();
};

#endif // WORLDOBJECT_H
