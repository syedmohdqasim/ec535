#include "scene.h"

#include <QDebug>

Scene::Scene(QGraphicsScene *parent)
    : QGraphicsScene{parent}
{
    moleTimeDuration = 1000;
    moleHoles();
    setUpMoleTimer();
//    this->setAcceptTouchEvents(True);
}

void Scene::startGame(){

     if(!moleTimer->isActive()){
        moleTimer->start(moleTimeDuration);
     }
}

void Scene::restartGame(){
    disconnect(Scene::connection);
    Game::resetScore();
}

void Scene::setUpMoleTimer()
{
    moleTimer = new QTimer(this);
    Scene::connection = connect(moleTimer, &QTimer::timeout,[=](){

        int randomIndex =  QRandomGenerator::global()->bounded(holePoints.size());
        Mole * mole1 = new Mole(holePoints[randomIndex]);
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
    holePoints.append(QPointF(50, 60));
    holePoints.append(QPointF(150, 60));
    holePoints.append(QPointF(250, 60));
    holePoints.append(QPointF(345, 60));

    holePoints.append(QPointF(50, 150));
    holePoints.append(QPointF(150, 150));
    holePoints.append(QPointF(250, 150));
    holePoints.append(QPointF(345, 150));

    //qDebug() << holePoints.size();

}
