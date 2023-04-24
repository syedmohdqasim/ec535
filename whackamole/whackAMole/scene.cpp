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

    gametimer->setInterval(1000); //30000
    connect(gametimer, &QTimer::timeout, [=]() {
        restartGame();
    });
    gametimer->start();

}

QList<QPointF> Scene::holePoints;

void Scene::startGame(){
    hideGameOver();
     if(!moleTimer->isActive()){
        moleTimer->start(moleTimeDuration);
     }
}

void Scene::restartGame(){
    disconnect(connection);
    Game::resetScore();
    showGameOver();
}


void Scene::showGameOver()
{
    qDebug() << "game over";
    //gameOverPix = new QGraphicsPixmapItem(QPixmap("image");//make image
   // addItem(gameOverPix);
   // gameOverPix -> setPos(center)//center
   scoreTextItem = new QGraphicsTextItem(); //include class
    // make sure that these are existing

   QString scoreString = "<p> Score : " + QString::number(Game::score) + "</p>" + "<p> Best Score : " + QString::number(Game::bestScore) + "</p>";
   //make look nice
   scoreTextItem -> setHtml(scoreString);
   addItem(scoreTextItem);
   // set under item
}

void Scene::hideGameOver()
{
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
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
