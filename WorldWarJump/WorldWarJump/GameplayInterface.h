#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>
#include "soundplayer.h"
class PhysicsCalc;

/**
 * @brief The GameplayInterface class displays the Terrain, and the players' multiple BattleUnit and Projectile.
 *
 * Furthermore, the GameplayInterface contains our physical engine PhysicsCalc.
 */
class GameplayInterface : public QGraphicsScene {
    Q_OBJECT
public:
    GameplayInterface(SoundPlayer * soundplayer);
    PhysicsCalc *physicsCalulator;


};

#endif // GAMEPLAYINTERFACE_H
