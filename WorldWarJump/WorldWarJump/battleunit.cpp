#define _USE_MATH_DEFINES
#include <cmath>

#include "battleunit.h"
#include "projectile.h"
#include <QDebug>
#include "gamesettings.h"

/**
 * @brief BattleUnit::BattleUnit constructor
 * @param parentView pointer to connect() the BattleUnit to the player's input and the game's refresh rate.
 * @param player
 * @param soundplayer
 * @param unittype
 *
 * The BattleUnit is only allowed to shoot every certain milliseconds, set in GameSettings.
 */
BattleUnit::BattleUnit(GameWorld * parentView, Player player,SoundPlayer *soundplayer, unitType unittype) : WorldObject(parentView, player, soundplayer)
{
    GameSettings * settings;
    soundpointer = soundplayer;
    ObjectType = 'b';
    this->parentView = parentView;
    this->ut=unittype;
    setPicture();
    this->setProjectile(0);
    double newCenter[2];
    shootTimer= new QTimer();
    shootTimer->start(settings->getMilisecondsBetweenBattleUnitShots());
    connect(shootTimer,SIGNAL(timeout()),this,SLOT(setShootAble()));
    switch(this->ut){
        case Tank:

            newCenter[0] = static_cast<int>(this->pixmap().width()*(30.0/100.0));
            newCenter[1] = static_cast<int>(this->pixmap().height()*(20.0/61.0));
            break;
        case Soldier:

            newCenter[0] = static_cast<int>(this->pixmap().width());
            newCenter[1] = static_cast<int>(this->pixmap().height());
            break;
        case Ship:

            newCenter[0] = static_cast<int>(this->pixmap().width()*(60.0/100.0));
            newCenter[1] = static_cast<int>(this->pixmap().height()*(20.0/62.0));
            break;
    }

//    qDebug() << "CenterX: " << newCenter[0] << "CenterY: " << newCenter[1] ;

    setCenterOfMass(newCenter);
    setTransformOriginPoint(getCenterOfMass()[0], getCenterOfMass()[1]);

    switch(player){
        case player1:
            connect(parentView->input, SIGNAL(playerOneJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerOneShoot()), this, SLOT(shoot()));

        break;
        case player2:
            connect(parentView->input, SIGNAL(playerTwoJump()), this, SLOT(jump()));
            connect(parentView->input, SIGNAL(playerTwoShoot()), this, SLOT(shoot()));
        break;
    }
    connect(parentView->input->refreshRateTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(parentView->input->refreshRateTimer, SIGNAL(timeout()), this, SLOT(move()));
    this->p=player;
    this->setWeight(100);
    this->setDamage(5);
    this->setHealthpoints(100);
    this->setRotVel(0);
    //Better use world timer, do we need input timer at all?
    setFlag(QGraphicsItem::ItemIsFocusable);
}


double BattleUnit::getFiredirection(){
    return this->firedirection;
}

void BattleUnit::setFiredirection(double direction){
    this->firedirection=direction;
}

unitType BattleUnit::getUnittype()
{
    return this->ut;
}

void BattleUnit::calculateShootingPoint(double * Point)
{

    unitType u = getUnittype();
    QPointF qpoint;
    switch(u){
        case Tank:

            //qpoint = this->sceneTransform().map(QPointF(this->pixmap().width(),this->pixmap().height()));
            qpoint = this->sceneTransform().map(QPointF(95,-7));
            break;
        case Soldier:

            qpoint = this->sceneTransform().map(QPointF(this->pixmap().width(),this->pixmap().height()));
            break;
        case Ship:

            qpoint = this->sceneTransform().map(QPointF(-10,40));
            break;
    }

    Point[0] = qpoint.x();
    Point[1] = qpoint.y();
}

/**
 * @brief BattleUnit::setPicture is a switch statement on the player and unitType to select the correct QGraphicsPixmapItem to display.
 */
void BattleUnit::setPicture()
{
    Player p = getPlayer();
    unitType u= getUnittype();
    switch(p){
        case player1:
            switch(u){
                case Tank:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Soldier:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Ship:
                    setPixmap(QPixmap(":/images/redship100.png"));
                break;
            }
        break;
        case player2:
            switch(u){
                case Tank:
                    setPixmap(QPixmap(":/images/bluetank100.png"));
                break;
                case Soldier:
                    setPixmap(QPixmap(":/images/redtank100.png"));
                break;
                case Ship:
                    setPixmap(QPixmap(":/images/blueship100.png"));
                break;
            }
        break;
    }
}

/**
 * @brief BattleUnit::shoot
 * This
 */
void BattleUnit::shoot(){
    if(ableToShoot){
        double nozzle[2];
        calculateShootingPoint(nozzle);
        qDebug() <<getProjectile();
        switch(this->getProjectile()%3){
        case 0:
            new Projectile(parentView, this, balistic, soundpointer, nozzle);
            soundpointer->playProjectileTypeShoot(1);
            //If you are confused by the indexes look for playProjectileTypeShoot function
            //in soundplayer. The switch case numbers give you what to play, URL names are descriptive
            break;
        case 1:
            new Projectile(parentView, this, ray, soundpointer ,nozzle);
            soundpointer->playProjectileTypeShoot(2);
            break;
        case 2:
            new Projectile(parentView, this, missile, soundpointer, nozzle);
            soundpointer->playProjectileTypeShoot(0);
            break;
        }
        ableToShoot=false;
    }
}

void BattleUnit::setShootAble(){
    this->ableToShoot=true;
}
