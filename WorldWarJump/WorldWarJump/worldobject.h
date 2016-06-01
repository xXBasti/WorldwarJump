#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"
#include "gameworld.h"
class GameWorld;

class WorldObject : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WorldObject(GameWorld *parentView);
    void setSpeed(double* newSpeed);
    double* getSpeed();

private:
    Input * input;
    double speed [2];
    void getNewValuesFromPhysicsCalc();
public slots:
    void move();
    void jump();
};

#endif // WORLDOBJECT_H
