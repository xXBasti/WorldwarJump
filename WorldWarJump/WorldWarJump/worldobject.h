#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "input.h"

class WorldObject : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WorldObject(Input* passInput);
private:
    Input *input;
public slots:
    void move();
};

#endif // WORLDOBJECT_H
