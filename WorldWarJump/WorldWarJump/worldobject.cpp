#include "worldobject.h"
#include <QGraphicsScene>
#include <QDebug>
#include "GameplayInterface.h"

#include "physicscalc.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "gamesettings.h"

#define M_PI 3.14159



/**
 * @brief WorldObject::move
 *
 */
void WorldObject::move()
{
    getNewValuesFromPhysicsCalc();
}
void WorldObject::hit(){
    ((GameplayInterface*)scene())->physicsCalulator->hitUnit(this);
}

void WorldObject::jump()
{
    double centerToObject[2] = {0};
    ((GameplayInterface*)scene())->physicsCalulator->gravVec(this,centerToObject);
    double distanceToCenter = ((GameplayInterface*)scene())->physicsCalulator->vectorsAbsoluteValue(centerToObject);

    if(distanceToCenter > 250){

        double speedPol[2];
        double speedEul[2];

        speedPol[0] = 7;
        speedPol[1] = ((orientation-90)/180)*M_PI;

        ((GameplayInterface*)scene())->physicsCalulator->polToEul(speedPol,speedEul,'v');

        speed[0] = speedEul[0] + speed[0];
        speed[1] = speedEul[1] + speed[1];

        //Create a randm variable that gives -1 or 1
        std::srand(std::time(0));
        int random_var = static_cast<int>(((rand()%2) -0.5)*2);
        qDebug() << "Random Variable: " <<random_var;
        //Introduce chance in rotation
        setRotVel(random_var *5 + getRotVel());

    }
    /*qDebug() << "Distance to Center:" << distanceToCenter;
    QPointF point(this->getCenterOfMass()[0],this->getCenterOfMass()[1]);
    qDebug() << "Center: " << this->sceneTransform().map(point);
    qDebug() << "Orientation" << orientation;*/
    /*qDebug() << "bottom left: " << this->sceneTransform().map(this->boundingRect().bottomLeft());
    qDebug() << "bottom right: " << this->sceneTransform().map(this->boundingRect().bottomRight());
    qDebug() << "Top left: " << this->scenePos();
    qDebug() << "Top left: " << this->sceneTransform().map(QPointF(0, 0));
    qDebug() << "Top right: " << this->sceneTransform().map(this->boundingRect().topRight());*/
    double * impactPoint = {0};
    getTopRight(impactPoint);
    qDebug() << "Furthest:" << QPointF(impactPoint[0],impactPoint[1]);

 }


WorldObject::WorldObject(GameWorld * parentView, Player p) {

    this->parentView = parentView;
    this->p = p;
    speed[0] = speed[1] = 0;
    setOrientation(0);
    setRotVel(0);

    ///*this->parentView = parentView;
    ///*setPixmap(QPixmap(":/images/worldobject.png"));
    double newCenter[2];
    newCenter[0] = 12.5;
    newCenter[1] = 40;
    setCenterOfMass(newCenter);
    setTransformOriginPoint(getCenterOfMass()[0], getCenterOfMass()[1]);
    //Apparently is more efficient for calculations:
    ///*this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    qDebug() << "Center of Mass: "<< centerOfMass[0] << " ; " << centerOfMass[1];
    //*setFlag(QGraphicsItem::ItemIsFocusable);

}

WorldObject::WorldObject(Player p) {

    this->p = p;
    speed[0] = speed[1] = 0;
    setOrientation(0);
    setRotVel(0);

    double newCenter[2];
    newCenter[0] = 12.5;
    newCenter[1] = 40;
    setCenterOfMass(newCenter);
    setTransformOriginPoint(getCenterOfMass()[0], getCenterOfMass()[1]);
}


double * WorldObject::getSpeed(){
    return speed;
}

void WorldObject::getNewValuesFromPhysicsCalc()
{
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewRotValues(this);
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewValues(this);

}

Player WorldObject::getPlayer() const
{
    return p;
}

void WorldObject::setSpeed(double *newSpeed){
    //Limit to max Speed
    double objectspeed = sqrt(newSpeed[0]*newSpeed[0] + newSpeed[1]*newSpeed[1]);
    double speedlimit = 200;
    if(objectspeed > speedlimit) {
        newSpeed[0] = newSpeed[0]*(speedlimit/objectspeed);
        newSpeed[1] = newSpeed[1]*(speedlimit/objectspeed);
    }
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

void WorldObject::getTopRight(double *topRight)
{
    QPointF point = this->sceneTransform().map(this->boundingRect().topRight());
    topRight[0] = point.x();
    topRight[1] = point.y();
}

void WorldObject::setHitCounter(int hit)
{
    this->hitcounter=hit;
}

int WorldObject::getHitCounter()
{
    return this->hitcounter;
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

int WorldObject::getWeight()
{
    return this->weigth;
}

void WorldObject::setWeight(int w)
{
    this->weigth=w;
}

int WorldObject::getHealthpoints(){
    return this->healthpoints;
}

int WorldObject::getDamage()
{
    return this->damage;
}

void WorldObject::setDamage(int d)
{
    this->damage=d;
}

void WorldObject::setHealthpoints(int points){
    this->healthpoints=points;
}

WorldObject::~WorldObject() {
    qDebug() <<"Terminated!";
}


