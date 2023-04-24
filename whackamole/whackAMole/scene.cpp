#include "scene.h"

#include <QDebug>

Scene::Scene(QGraphicsScene *parent)
    : QGraphicsScene{parent}
{
    gameOn = false;
    moleTimeDuration = 1000;
    Scene::selfptr= this;
    moleHoles();
    startGame();
}

QList<QPointF> Scene::holePoints;
Scene * Scene::selfptr;

void Scene::startGame(){
    Scene::selfptr->hideGameOver();
    //qDebug() << "start game"<<Scene::selfptr;
    // qDebug() << Scene::selfptr;
    Scene::selfptr->setUpMoleTimer();
    //qDebug() << "new game timer";
     QTimer::singleShot(3000, [=](){ // change this time for slower
         //qDebug() << "game timer expired";
         Scene::selfptr->restartGame();
     });
     //qDebug() << "new game timer";
}

void Scene::restartGame(){
    //qDebug() << "restart game";
    finalScore = Game::score;

    disconnect(connection);
    //qDebug() << "disconnected connection";

    moleTimer->stop();
    //qDebug() << "stopped timer";

    moleTimer->deleteLater();
    //qDebug() << "deleted timer";

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

   QString scoreString = "<p> Score : " + QString::number(finalScore) + "</p>" + "<p> Best Score : " + QString::number(Game::bestScore) + "</p>";
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
    qDebug() << "inside mole timer"<<moleTimer->isActive();
    //qDebug() << Scene::selfptr << "hi";

    moleTimer = new QTimer(Scene::selfptr);


    qDebug() << "new mole timer";
    connection = connect(moleTimer, &QTimer::timeout,[=](){

        int randomIndex =  QRandomGenerator::global()->bounded(Scene::holePoints.size());
        Mole * mole1 = new Mole(Scene::holePoints[randomIndex]);
        Scene::holePoints.removeAt(randomIndex);
        addItem(mole1);
    });
    qDebug() << "connected timer";
    moleTimer->start(moleTimeDuration); //can change

    qDebug() << "mole timer started";
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
