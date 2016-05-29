#include "input.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>


Input::Input(){
    setRect(0,0,50,50);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}


Input::~Input(){
}

void Input::keyPressEvent(QKeyEvent *k){
    qDebug() << "key pressed";
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

