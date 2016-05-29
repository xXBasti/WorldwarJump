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
    setRect(0,0,100,100);
    connect(passInput, SIGNAL(playerOneJump()), this, SLOT(move()));
    this->input = passInput;
    setFlag(QGraphicsItem::ItemIsFocusable);
}
