#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

#include "physicscalc.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

#define M_PI 3.14159



/**
 * @brief WorldObject::move
 *
 */
void WorldObject::move()
{
    getNewValuesFromPhysicsCalc();
}

void WorldObject::jump()
{
    //speed[1] = -8;
    double speedPol[2];
    double speedEul[2];
    speedPol[0] = 5;
    speedPol[1] = ((orientation-90)/360)*2*M_PI;

    ((GameplayInterface*)scene())->physicsCalulator->polToEul(speedPol,speedEul,'v');

    speed[0] = speedEul[0] + speed[0];
    speed[1] = speedEul[1] + speed[1];

    //Create a randm variable that gives -1 or 1
    /*std::srand(std::time(0));
    int random_var = static_cast<int>(((rand()%2) -0.5)*2);
    qDebug() << random_var;*/
    //Introduce chance in rotation
    //rotVel = random_var *1 + rotVel;
    rotVel = 5 + rotVel;
    qDebug() << "Orientation" << orientation;
    qDebug() << "bottom left: " << this->sceneTransform().map(this->boundingRect().bottomLeft());
    qDebug() << "bottom right: " << this->sceneTransform().map(this->boundingRect().bottomRight());
    qDebug() << "Top left: " << this->scenePos();
    qDebug() << "Top left: " << this->sceneTransform().map(QPointF(0, 0));
    qDebug() << "Top right: " << this->sceneTransform().map(this->boundingRect().topRight());

 }


WorldObject::WorldObject(GameWorld * parentView) {

    this->parentView = parentView;
    setPixmap(QPixmap(":/images/worldobject.png"));
    setTransformOriginPoint(centerOfMass[0], centerOfMass[1]);
    //Apparently is more efficient for calculations:
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    setFlag(QGraphicsItem::ItemIsFocusable);
}


double * WorldObject::getSpeed(){
    return speed;
}

void WorldObject::getNewValuesFromPhysicsCalc()
{
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewValues(this);
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewRotValues(this);
}

void WorldObject::setSpeed(double *newSpeed){
    speed[0] = newSpeed[0];
    speed[1] = newSpeed[1];
}

void WorldObject::getPosition(double *outputPointer)
{
    outputPointer[0] = x();
    outputPointer[1] = y();
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

void WorldObject::setCenterOfMass(double *newCenterOfMass)
{
    centerOfMass[0] = newCenterOfMass[0];
    centerOfMass[1] = newCenterOfMass[1];
}

double *WorldObject::getCenterOfMass()
{
    return centerOfMass;
}

