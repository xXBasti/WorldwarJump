#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "gamesettings.h"

class BackGround : public QGraphicsPixmapItem
{
public:
    BackGround(GameSettings *settings, QTimer *backGroundRotationTimer);
private:
    int stage;
    int gameWorldSize;
};

#endif // BACKGROUND_H
