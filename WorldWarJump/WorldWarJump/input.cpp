#include "input.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "gamesettings.h"

Input::Input(){
    GameSettings * settings;
    int gameWorldSize = settings->getGameWorldSize();
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    refreshRateTimer = new QTimer();
    refreshRateTimer->start(20);
    setRect(0,0,gameWorldSize,gameWorldSize);
}


Input::~Input(){
}

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

