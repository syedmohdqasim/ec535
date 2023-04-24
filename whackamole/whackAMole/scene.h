#ifndef SCENE_H
#define SCENE_H


#include "mole.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QPointF>
#include <QList>
#include <QRandomGenerator>
#include <QFont>
#include <QGraphicsTextItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsScene *parent = nullptr);
    void startGame();
    void restartGame();
    void hideGameOver();
    static QList<QPointF> holePoints;
    static Scene * selfptr;
    static QGraphicsTextItem * scoreTextItem;
    static QGraphicsPixmapItem * gameOverPix;
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


    QMetaObject::Connection connection;
    int finalScore;

    void moleHoles();
    void showGameOver();
};

#endif // SCENE_H
