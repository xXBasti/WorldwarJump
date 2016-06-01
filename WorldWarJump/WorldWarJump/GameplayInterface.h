#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>
#include "physicscalc.h"

class GameplayInterface : public QGraphicsScene {
    Q_OBJECT
public:

        GameplayInterface();
        PhysicsCalc * physicsCalulator;
};

#endif // GAMEPLAYINTERFACE_H
