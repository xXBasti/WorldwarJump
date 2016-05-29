#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>
#include <QTimer>

class GameplayInterface : public QGraphicsScene
{
    public:

        GameplayInterface();
//Implemented pause and resume
        void pause();
        void resume();

    private:

        //! Gameplay refresh rate
        QTimer *timer = new QTimer;
};

#endif // GAMEPLAYINTERFACE_H
