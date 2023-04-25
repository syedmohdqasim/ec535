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
#include "MediumButtonTouchableGraphicsItem.h"
#include "HardButtonTouchableGraphicsItem.h"
#include "EasyButtonTouchableGraphicsItem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsScene *parent = nullptr);
    void startGame();
    void restartGame();
    void hideGameOver();
    void showMenu();
    void hideMenu();
    static QList<QPointF> holePoints;
    static Scene * selfptr;
    static QGraphicsTextItem * scoreTextItem;
    static QGraphicsPixmapItem * gameOverPix;
    static QGraphicsPixmapItem * menuPix;
    static EasyButtonTouchableGraphicsItem * easyButtonPix;
    static HardButtonTouchableGraphicsItem * hardButtonPix;
    static MediumButtonTouchableGraphicsItem * mediumButtonPix;

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
