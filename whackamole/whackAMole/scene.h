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
    static Scene * selfptr;
//    static QMetaObject::Connection connection;
protected:
    void touchEvent(QTouchEvent *event);
signals:

private:
    bool gameOn;
    void setUpMoleTimer();
    int moleTimeDuration;
    QTimer * moleTimer;
    QTimer * gametimer;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsPixmapItem * gameOverPix;

    QMetaObject::Connection connection;
    int finalScore;

    void moleHoles();
    void hideGameOver();
    void showGameOver();
};

#endif // SCENE_H
