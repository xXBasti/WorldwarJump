#ifndef TERRAIN_H
#define TERRAIN_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "gameworld.h"

//! Terrain, the playground for our battle units in form of an inner circle. - WANG
class Terrain : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Terrain();
};

#endif // TERRAIN_H
