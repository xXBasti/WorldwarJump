#include "GameplayInterface.h"
#include <QDebug>
#include "physicscalc.h"

GameplayInterface::GameplayInterface()
{
    gameWorldSize = settings->getGameWorldSize();
    physicsCalulator = new PhysicsCalc();
    timer = new QTimer();
    timer->start(20);

    input = new Input();
    input->setRect(0,0,gameWorldSize,gameWorldSize);
    this->addItem(input);
}

void GameplayInterface::createAndAddUnits()
{
    int player1UnitCount = (int)settings->getPlayer1UnitCount();
    for(int i=1; i <= player1UnitCount; i++){
    }
}

