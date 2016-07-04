#include "input.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "gamesettings.h"

/**
 * @brief Input::Input
 * This function is the constructor of the Input class.
 *
 */
Input::Input(){
    GameSettings * settings;
    int gameWorldSize = settings->getGameWorldSize();
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    refreshRateTimer = new QTimer();
    refreshRateTimer->start(20);
    setRect(0,0,gameWorldSize,gameWorldSize);
}

/**
 * @brief Input::~Input
 * Destructor of the Input class.
 */
Input::~Input(){
}

/**
 * @brief Input::keyPressEvent
 * This function reacts on any keyboard input and emit a signal if the control buttons for
 * player one or player two had been pressed.
 * @param k is the keyboard button which has been pressed.
 */
void Input::keyPressEvent(QKeyEvent *k){
    if(k->key() ==Qt::Key_Up){
    emit this->playerOneJump();
    }
    if(k->key() ==Qt::Key_Right){
    emit this->playerOneShoot();
    }
    if(k->key()==Qt::Key_W){
    emit this->playerTwoJump();
    }
    if(k->key()==Qt::Key_E){
    emit this->playerTwoShoot();
    }
}

