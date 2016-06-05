#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>

void WorldObject::move()
{
    qDebug() << "move command received";
    setPos(x(), y()-10);
}

WorldObject::WorldObject(Input* passInput)
{
    setRect(0,0,700,700);
    connect(passInput, SIGNAL(playerOneJump()), this, SLOT(move()));
    connect(passInput, SIGNAL(playerTwoJump()), this, SLOT(move()));
    connect(passInput, SIGNAL(playerOneShoot()), this, SLOT(move()));
    connect(passInput, SIGNAL(playerTwoShoot()), this, SLOT(move()));
    this->input = passInput;
    setFlag(QGraphicsItem::ItemIsFocusable);
}


//For Orientation
void WorldObject::setOrientation(double newOrientation)
{
    this->orientation = newOrientation;

}

double WorldObject::getOrientation() const
{
    return(orientation);
}

void WorldObject::setRotVel(double newRotVel)
{
    this->rotVel = newRotVel;
}

double WorldObject::getRotVel() const
{
    return(rotVel);
}
//For Orientation
