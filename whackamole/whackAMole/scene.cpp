#include "scene.h"

#include <QDebug>

Scene::Scene(QGraphicsScene *parent)
    : QGraphicsScene{parent}
{
    moleTimeDuration = 1000;
    moleHoles();
    setUpMoleTimer();
//    this->setAcceptTouchEvents(True);
    QTimer *gametimer = new QTimer(this);

    gametimer->setInterval(30000);
    connect(gametimer, &QTimer::timeout, [=]() {
        restartGame();
    });
    gametimer->start();

}

QList<QPointF> Scene::holePoints;

void Scene::startGame(){

     if(!moleTimer->isActive()){
        moleTimer->start(moleTimeDuration);
     }
}

void Scene::restartGame(){
    disconnect(connection);
    Game::resetScore();

}

void Scene::setUpMoleTimer()
{
    moleTimer = new QTimer(this);
    connection = connect(moleTimer, &QTimer::timeout,[=](){

        int randomIndex =  QRandomGenerator::global()->bounded(Scene::holePoints.size());
        Mole * mole1 = new Mole(Scene::holePoints[randomIndex]);
        Scene::holePoints.removeAt(randomIndex);
        addItem(mole1);
    });

    moleTimer->start(moleTimeDuration); //can change
}

void Scene::touchEvent(QTouchEvent *event)
{
    qDebug() << "touch pressed";
}

void Scene::moleHoles(){
    //QList<QPointF> holePoints;
    Scene::holePoints.append(QPointF(50, 60));
    Scene::holePoints.append(QPointF(150, 60));
    Scene::holePoints.append(QPointF(250, 60));
    Scene::holePoints.append(QPointF(345, 60));

    Scene::holePoints.append(QPointF(50, 150));
    Scene::holePoints.append(QPointF(150, 150));
    Scene::holePoints.append(QPointF(250, 150));
    Scene::holePoints.append(QPointF(345, 150));

    //qDebug() << holePoints.size();

}
