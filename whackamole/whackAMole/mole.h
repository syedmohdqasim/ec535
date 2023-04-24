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

class mole : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit mole(QPointF place);
    ~mole();
    void setEnabled(bool enabled);
    bool didItHit();
    QPointF getLocation();
    void setHit(bool hitted);
    void setLocation(QPointF point);
signals:

protected:
    void touchEvent(QTouchEvent *event); //override
private:
    QPointF location;
    bool hit; //0 : no, 1: yes
    //void onAnimationFinished();
    //void onAnimationFinished2();
    void visible(mole *obj);
};

#endif // MOLE_H
