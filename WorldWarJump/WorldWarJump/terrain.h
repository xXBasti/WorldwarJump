#ifndef TERRAIN_H
#define TERRAIN_H

#include <QGraphicsPixmapItem>

#include "gameworld.h"
#include "gamesettings.h"
#include "GameplayInterface.h"
#include <QTimer>
#include <QObject>

//! Terrain, the playground for our battle units in form of an inner circle. - WANG
class Terrain : public QGraphicsPixmapItem
{
public:
    Terrain(GameSettings *settings, GameplayInterface *scene);
private:
    int stage;
};

#endif // TERRAIN_H
