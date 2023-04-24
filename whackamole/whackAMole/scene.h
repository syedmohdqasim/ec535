#ifndef SCENE_H
#define SCENE_H


#include "mole.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QPointF>
#include <QList>
#include <QRandomGenerator>
#include <QGraphicsTextItem>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsScene *parent = nullptr);
    void startGame();
    void restartGame();
    static QList<QPointF> holePoints;
//    static QMetaObject::Connection connection;
protected:
    void touchEvent(QTouchEvent *event);
signals:

private:
    void setUpMoleTimer();
    int moleTimeDuration;
    QTimer * moleTimer;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsPixmapItem * gameOverPix;

    QMetaObject::Connection connection;


    void moleHoles();
    void hideGameOver();
    void showGameOver();
};

#endif // SCENE_H
