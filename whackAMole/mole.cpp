#include "mole.h"

#include <QDebug>
#include "scene.h"
#include <game.h>

// may need to make a button
Mole::Mole(QPointF place)
{
    //hit = 0;
    setVisible(false);
    setAcceptTouchEvents(true);
    location = place;
    setPos(location);
    setPixmap(QPixmap(":/images/mole.png"));
    qDebug() << "New mole at" << location;
    visible(this);
}


//called when mole is whacked/touched.

bool Mole::sceneEvent(QEvent* event)  {
    qDebug() << "some event mole touch";
    if (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchEnd) {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        for (const QTouchEvent::TouchPoint& touchPoint : touchEvent->touchPoints()) {
            if (touchPoint.state() == Qt::TouchPointPressed || touchPoint.state() == Qt::TouchPointMoved || touchPoint.state() == Qt::TouchPointStationary) {
                QPointF pos = touchPoint.pos();
                qDebug() << "Touch point id:" << touchPoint.id() << "x:" << pos.x() << "y:" << pos.y();
                qDebug() << "Hit mole.";
                setPixmap(QPixmap(":/images/mole_hit.png"));
                //hit = 1;
                hit(this);

            }
        }
    }

    return QGraphicsPixmapItem::sceneEvent(event);
};

//method that makes mole visible for some duration.
void Mole::visible(Mole *obj) {
    obj->setVisible(true);
    obj->setAcceptTouchEvents(true);
    QTimer::singleShot(Game::moleAppearanceDuration, [=](){ // change this time for slower
        obj->setVisible(false);
        Scene::holePoints.append(location);
        qDebug() << obj->location;
        delete obj;
    });
}



void Mole::touchEvent(QTouchEvent* event) {
    if (!isVisible()) { // if the item is disabled, do nothing
        return;
    }
    if (isVisible()) { // if the item is visible, spin it
        qDebug() << "Hit mole.";
        setPixmap(QPixmap(":/images/mole_hit.png"));
      //  hit = 1;
        setVisible(false);
    }
}

void Mole::hit(Mole *obj){
    if(obj->isVisible()){
    Game::score++;
    qDebug() << "score is:"<< Game::score;
    setVisible(false);
    }
};

bool Mole::didItHit(){
    return 0;
}

void Mole::setHit(bool hitted){
   // this->hit = hitted;

}

QPointF Mole::getLocation(){
    return location;
}

void Mole::setLocation(QPointF point){
    location = point;
    setPos(location);
}

Mole::~Mole(){
    qDebug() << "Deleting mole.";
}
