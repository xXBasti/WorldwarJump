#ifndef GAMEPLAYINTERFACE_H
#define GAMEPLAYINTERFACE_H

#include <QGraphicsScene>


class GameplayInterface : public QGraphicsScene
{
    public:
        GameplayInterface();

        void exit();

        void pause();

    private:


};

#endif // GAMEPLAYINTERFACE_H
