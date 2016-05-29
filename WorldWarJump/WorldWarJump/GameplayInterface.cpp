#include "GameplayInterface.h"
#include <QDebug>

GameplayInterface::GameplayInterface()
{
    timer->start(20);

}

void GameplayInterface::pause()
{
    timer->stop();

}

void GameplayInterface::resume()
{
    timer->start(20);

}
