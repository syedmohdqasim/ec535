#ifndef MOLE_H
#define MOLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent> //not necessary
#include <QTouchEvent>
#include "game.h"

class Mole : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Mole(QPointF place);
    ~Mole();
    void setEnabled(bool enabled);
    bool didItHit();
    QPointF getLocation();
    void setHit(bool hitted);
    void setLocation(QPointF point);
    void hit(Mole *obj);
signals:

protected:
    bool sceneEvent(QEvent* event) override;
    void touchEvent(QTouchEvent *event) ; //override
private:
    QPointF location;
//    bool hit; //0 : no, 1: yes
    //void onAnimationFinished();
    //void onAnimationFinished2();
    void visible(Mole *obj);
};


#endif // MOLE_H
