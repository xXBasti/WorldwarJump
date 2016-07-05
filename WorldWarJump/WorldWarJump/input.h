#ifndef INPUT_H
#define INPUT_H
#include <QGraphicsRectItem>
#include <QTimer>

/**
 * @brief The Input class receives the players' key hits
 *
 * Detailed: it is the focused QGraphicsPixmapItem in our GameplayInterface scene, and therefore able to receive
 * keyboard input. It receives the input for both players and sends according SIGNALs.
 *
 * Also because of early architecture decisions, it has the QTimer refreshRateTimer which is connected() with every unit
 * and projectile in our game. This QTimer triggers the move() function in WorldObject every certain amount of milliseconds set in GameSettings. -Tomas
 */
class Input : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Input();
    void keyPressEvent(QKeyEvent *k);
    //! Gameplay refresh rate
    QTimer * refreshRateTimer;
    ~Input();

signals:
    void playerOneJump();
    void playerOneShoot();
    void playerTwoJump();
    void playerTwoShoot();
};

#endif // INPUT_H
