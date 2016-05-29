#ifndef INPUT_H
#define INPUT_H
#include <QGraphicsRectItem>

class Input : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Input();
    void keyPressEvent(QKeyEvent *k);
    ~Input();
signals:
    void playerOneJump();
    void playerOneShoot();
    void playerTwoJump();
    void playerTwoShoot();
};

#endif // INPUT_H
