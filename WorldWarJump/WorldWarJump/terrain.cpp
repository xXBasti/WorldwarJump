#include "terrain.h"
#include "gamesettings.h"
#include "physicscalc.h"
#include "GameplayInterface.h"

Terrain::Terrain(GameSettings *settings, GameplayInterface *scene)
{

    int stage = settings->getWhichStage();
    switch(stage)
    {
    case 2:
        this->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/Battleground_Front.png"));
        scene->physicsCalulator->gravity = settings->getGravity();
        scene->physicsCalulator->bounceB4Destruction = settings->getJumpCountForDestruction();

        break;
    case 1:
        this->setPixmap(QPixmap(":/images/pics/TerrainAndBackgrounds/weltallterrain.png"));
        scene->physicsCalulator->gravity = 0;
        scene->physicsCalulator->bounceB4Destruction = 4;

        break;
    }
}
