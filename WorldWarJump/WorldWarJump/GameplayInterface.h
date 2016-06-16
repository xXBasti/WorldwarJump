#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>
#include "gamesettings.h"
#include "input.h"
#include <QTimer>
class PhysicsCalc;

class GameplayInterface : public QGraphicsScene {
    Q_OBJECT
public:
    Input * input;
    QTimer * timer;
    GameplayInterface();
    PhysicsCalc * physicsCalulator;
private:
    GameSettings * settings;
    int gameWorldSize;
    void createAndAddUnits();
};

#endif // GAMEPLAYINTERFACE_H
