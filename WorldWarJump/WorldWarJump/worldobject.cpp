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
 * This function is called every timestep and gets the new position and speed values for the WorldObject from the physicscalc.
 */
void WorldObject::move()
{
    getNewValuesFromPhysicsCalc();
}

/**
 * @brief WorldObject::hit
 * This function is called every timestep by ervery Projectile subclass to check if itself hit any WorldObject.
 */
void WorldObject::hit(){
    ((GameplayInterface*)scene())->physicsCalulator->hitUnit(this);
}

/**
 * @brief WorldObject::jump makes the unit jump in the direction of its head and introduces random rotation.
 * The unit is able to jump in certain proximity to the ground, or when it is colliding with an other unit.
 * The rotation has constant magnitude, but the direction is random.
 */
void WorldObject::jump()
{
    double centerToObject[2] = {0};
    ((GameplayInterface*)scene())->physicsCalulator->gravVec(this,centerToObject);
    double distanceToCenter = ((GameplayInterface*)scene())->physicsCalulator->vectorsAbsoluteValue(centerToObject);

    if(distanceToCenter > 250 || this->okToJump || ((GameplayInterface*)scene())->physicsCalulator->collideWithAny(this)){

        soundpointer->playJump();
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
        //Introduce chance in rotation
        setRotVel(random_var *5 + getRotVel());


    }
 }

/**
 * @brief WorldObject::WorldObject constructor.
 * @param parentView pointer to connect() the BattleUnit to the player's input and the game's refresh rate.
 * @param p the player controlling the unit
 * @param soundplayer the pointer to the global sound player
 */
WorldObject::WorldObject(GameWorld * parentView, Player p,SoundPlayer *soundplayer) {

    soundpointer=soundplayer;

    jumpCounter = 20;
    okToJump = false;
    ObjectType = 'o';
    this->parentView = parentView;
    this->p = p;
    speed[0] = speed[1] = 0;
    setOrientation(0);
    setRotVel(0);
    this->setFirstcollide(true);
    ///*this->parentView = parentView;
    ///*setPixmap(QPixmap(":/images/worldobject.png"));
    double newCenter[2];
    newCenter[0] = 12.5;
    newCenter[1] = 40;
    this->setSpeed(speed);
    setCenterOfMass(newCenter);
    setTransformOriginPoint(getCenterOfMass()[0], getCenterOfMass()[1]);
    //Apparently is more efficient for calculations:
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);


}
/**
 * @brief WorldObject::getSpeed returns the speed of the unit
 * @return the pointer to the speed array
 */
double * WorldObject::getSpeed(){
    return speed;
}

/**
 * @brief WorldObject::getNewValuesFromPhysicsCalc
 * This function start the update of the old values by the physicsCalc class.
 */
void WorldObject::getNewValuesFromPhysicsCalc()
{
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewRotValues(this);
    ((GameplayInterface*)scene())->physicsCalulator->calculateNewValues(this);

}

bool WorldObject::getFirstcollide() const
{
    return firstcollide;
}

void WorldObject::setFirstcollide(bool col)
{
    firstcollide = col;
}

/**
 * @brief WorldObject::getBounced returns if the object has bounced before
 * @return if the object has bounced before
 */
bool WorldObject::getBounced() const
{
    return bounced;
}
/**
 * @brief WorldObject::setBounced sets if the object has bounced before
 * @param value the bool value indicating if the object has bounced before or not
 */
void WorldObject::setBounced(bool value)
{
    bounced = value;
}

/**
 * @brief WorldObject::getPlayer returns the player controlling the unit
 * @return the player controlling the unit
 */
Player WorldObject::getPlayer() const
{
    return p;
}

/**
 * @brief WorldObject::setSpeed set the speed of the unit and limit to a max speed
 * @param newSpeed the pointer to the new speed array
 */
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

/**
 * @brief WorldObject::setOrientation set the turning angle of the unit in degrees
 * @param newOrientation the new angle in degrees
 */
void WorldObject::setOrientation(double newOrientation)
{
    this->orientation = newOrientation;

}
/**
 * @brief WorldObject::getOrientation get the turning angle of the unit in degrees
 * @return the turning angle in degrees
 */
double WorldObject::getOrientation() const
{
    return(orientation);
}

/**
 * @brief WorldObject::setRotVel set the rotational velocity in degrees and limit it
 * @param newRotVel the new rotational velocity in degrees
 */
void WorldObject::setRotVel(double newRotVel)
{
    //Limit to max Rotational Velocity
    double absRotVel = sqrt(newRotVel*newRotVel);
    double rotVelLimit = 7;
    if(absRotVel > rotVelLimit) {
        newRotVel = newRotVel*(rotVelLimit/absRotVel);
    }
    this->rotVel = newRotVel;
}
/**
 * @brief WorldObject::getRotVel returns the rotational velocity in degrees
 * @return the rotational velocity in degrees
 */
double WorldObject::getRotVel() const
{
    return(rotVel);
}

/**
 * @brief WorldObject::setHitCounter set how many times the unit has hit the ground
 * @param hit the number of collisions with ground
 */
void WorldObject::setHitCounter(int hit)
{
    this->hitcounter=hit;
}
/**
 * @brief WorldObject::getHitCounter get how many times the unit has hit the ground
 * @return the number of collisions with ground
 */
int WorldObject::getHitCounter()
{
    return this->hitcounter;
}
//For Orientation

/**
 * @brief WorldObject::setCenterOfMass sets the position of units center of mass in scene coordinates
 * @param newCenterOfMass the new center of mass position
 */
void WorldObject::setCenterOfMass(double *newCenterOfMass)
{
    centerOfMass[0] = newCenterOfMass[0];
    centerOfMass[1] = newCenterOfMass[1];
}
/**
 * @brief WorldObject::getCenterOfMass gets the position of units center of mass in scene coordinates
 * @return the center of mass position
 */
double *WorldObject::getCenterOfMass()
{
    return centerOfMass;

}
/**
 * @brief WorldObject::getWeight returns the weight value of the unit
 * @return the weight
 */
int WorldObject::getWeight()
{
    return this->weigth;
}
/**
 * @brief WorldObject::setWeight sets the weight value of the unit
 * @param w the new weight value
 */
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

/**
 * @brief WorldObject::setHealthpoints
 * This function sets the Healthpoints and emit a signal with the healthpoints to the healthpointsbar.
 * @param points are the lifepoints
 */
void WorldObject::setHealthpoints(int points){
    this->healthpoints=points;
    if(healthpoints<0)
        healthpoints=0;
    emit this->sendHealth(healthpoints);
}

void WorldObject::setProjectile(int proj)
{
    this->projectilselector=proj;
}

int WorldObject::getProjectile()
{
    return projectilselector;
}
/**
 * @brief WorldObject::getChar returns the character indicating the unit type.
 * If it is a battle unit, the character is 'b'
 * If it is a projectile, the character is 'p'
 * If it is neither, the character is 'o'
 * @return the units type
 */
char WorldObject::getChar()
{
    return ObjectType;
}


WorldObject::~WorldObject() {
}


