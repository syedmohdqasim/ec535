#include "mole.h"

#include <QDebug>

// may need to make a button
mole::mole(QPointF place)
{
    hit = 0;
    setVisible(false);
    setAcceptTouchEvents(false);
    location = place;
    setPos(location);
    setPixmap(QPixmap(":/images/mole.png"));
    qDebug() << "New mole at" << location;
    visible(this);
}

void mole::visible(mole *obj) {
    obj->setVisible(true);
    obj->setAcceptTouchEvents(true);
    QTimer::singleShot(2000, [=](){ // change this time for slower
        obj->setVisible(false);
        qDebug() << obj->location;
        delete obj;
    });
}

/*
void mole::onAnimationFinished() {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::InQuad);
    connect(animation, &QPropertyAnimation::finished, this, &mole::onAnimationFinished2);
    animation->start();
    setEnabled(false); // disable the item when it is spinning
}

void mole::onAnimationFinished2() {
    setVisible(false); // hide the item after it disappears // neeed a timer herer
    setEnabled(true); // re-enable the item when it is hidden
    scene()->removeItem(this);
    delete this;
}
*/

void mole::touchEvent(QTouchEvent* event) {
    if (!isVisible()) { // if the item is disabled, do nothing
        return;
    }
    if (isVisible()) { // if the item is visible, spin it
        qDebug() << "Hit mole.";
        setPixmap(QPixmap(":/images/mole_hit.png"));
        hit = 1;
        setVisible(false);
    }
}

bool mole::didItHit(){
    return hit;
}

void mole::setHit(bool hitted){
    this->hit = hitted;
}

QPointF mole::getLocation(){
    return location;
}

void mole::setLocation(QPointF point){
    location = point;
    setPos(location);
}

mole::~mole(){
    qDebug() << "Deleting mole.";
}
