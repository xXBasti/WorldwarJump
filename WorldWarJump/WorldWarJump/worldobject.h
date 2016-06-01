#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"

class WorldObject : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WorldObject(Input* passInput);
    double* getSpeed();
    void setSpeed(qreal* newSpeed);
private:
    Input *input;
    double speed [2];
    void getNewValuesFromPhysicsCalc();
public slots:
    void move();
    void jump();
};

#endif // WORLDOBJECT_H
