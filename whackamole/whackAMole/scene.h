#ifndef SCENE_H
#define SCENE_H


#include "mole.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QPointF>
#include <QList>
#include <QRandomGenerator>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsScene *parent = nullptr);
    void startGame();
    void restartGame();
protected:
    void touchEvent(QTouchEvent *event);
signals:

private:
    void setUpMoleTimer();
    int moleTimeDuration;
    QTimer * moleTimer;
    QList<QPointF> holePoints;
    QMetaObject::Connection connection;


    void moleHoles();
};

#endif // SCENE_H
