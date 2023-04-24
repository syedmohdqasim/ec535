#include "scene.h"

#include <QDebug>

Scene::Scene(QGraphicsScene *parent)
    : QGraphicsScene{parent}
{
    gameOn = false;
    moleTimeDuration = 1000;
    Scene::selfptr= this;
    qDebug() << "self pointer";
    moleHoles();
    qDebug() << "holes made";
    startGame();
}

QList<QPointF> Scene::holePoints;
Scene * Scene::selfptr;
QGraphicsTextItem * Scene::scoreTextItem;
QGraphicsPixmapItem * Scene::gameOverPix;

void Scene::startGame(){
    qDebug() << "start game"<<Scene::selfptr;
    qDebug() << Scene::selfptr;
    Scene::selfptr->setUpMoleTimer();
    qDebug() << "new game timer";
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
    Scene::gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));//make image
    addItem(Scene::gameOverPix);
    Scene::gameOverPix -> setPos(10,30);
   Scene::scoreTextItem = new QGraphicsTextItem(); //include class
    // make sure that these are existing

   QString scoreString = "<p> Score : " + QString::number(finalScore) + "<p> Best Score : " + QString::number(Game::bestScore) + "</p>";
   //make look nice
   QFont mfont("Consolas", 30, QFont::Bold);
   Scene::scoreTextItem -> setHtml(scoreString);
   Scene::scoreTextItem ->setPos(80,100);
   Scene::scoreTextItem ->setFont(mfont);
   Scene::scoreTextItem ->setDefaultTextColor(Qt::white);
   addItem(Scene::scoreTextItem);
   // set under item
}

void Scene::hideGameOver()
{
   //qDebug() << "to be image hidden";
    Scene::gameOverPix->setVisible(false);
    //qDebug() << "score text hidden";
    Scene::scoreTextItem->setVisible(false);
}


void Scene::setUpMoleTimer()
{
    //qDebug() << Scene::selfptr << "hi";

    moleTimer = new QTimer(Scene::selfptr);


    //qDebug() << "new mole timer";
    connection = connect(moleTimer, &QTimer::timeout,[=](){

        int randomIndex =  QRandomGenerator::global()->bounded(Scene::holePoints.size());
        Mole * mole1 = new Mole(Scene::holePoints[randomIndex]);
        Scene::holePoints.removeAt(randomIndex);
        addItem(mole1);
    });
    //qDebug() << "connected timer";
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
