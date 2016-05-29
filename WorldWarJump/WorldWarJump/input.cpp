#include "input.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>


Input::Input()
{

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

void Input::playerOneJump(){


}

void Input::playerTwoJump(){


}
void Input::playerOneShoot(){


}
void Input::playerTwoShoot(){


}

