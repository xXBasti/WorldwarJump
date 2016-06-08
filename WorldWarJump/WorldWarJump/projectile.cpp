#include "projectile.h"
#include <QPainter>

Projectile::Projectile(GameWorld *parentView, int x,int y,projectileType pT) : WorldObject(parentView)
{
    int rx,ry;
    switch (pT){
    case missile:
        break;
    case balistic:
        break;
    case ray:
        break;
    case scrap:
        break;
    }

    QPainter painter(parentView);
    painter.setBrush(QBrush(Qt::black)); //Je nach typ
    painter.drawEllipse(QPoint(x,y),rx,ry);
}

void Projectile::fly(){



}

void Projectile::hit(){


}
