#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>
#include "soundplayer.h"
class PhysicsCalc;

class GameplayInterface : public QGraphicsScene {
    Q_OBJECT
public:
    GameplayInterface(SoundPlayer * soundplayer);
    PhysicsCalc *physicsCalulator;


};

#endif // GAMEPLAYINTERFACE_H
