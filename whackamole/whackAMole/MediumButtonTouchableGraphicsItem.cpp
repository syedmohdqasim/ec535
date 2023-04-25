//
// Created by sqasim on 4/23/23.
//
#include "MediumButtonTouchableGraphicsItem.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QEvent>
#include <QtGui>
#include <game.h>
#include "HardButtonTouchableGraphicsItem.h"
#include "EasyButtonTouchableGraphicsItem.h"
#include "scene.h"

MediumButtonTouchableGraphicsItem * MediumButtonTouchableGraphicsItem::selfptr;

void MediumButtonTouchableGraphicsItem::hide(){
    MediumButtonTouchableGraphicsItem::selfptr ->setVisible(false);
}

bool MediumButtonTouchableGraphicsItem::sceneEvent(QEvent* event)  {
        //qDebug() << "some event";
    if (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchEnd) {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        for (const QTouchEvent::TouchPoint& touchPoint : touchEvent->touchPoints()) {
            if (touchPoint.state() == Qt::TouchPointPressed || touchPoint.state() == Qt::TouchPointMoved || touchPoint.state() == Qt::TouchPointStationary) {
                QPointF pos = touchPoint.pos();
                qDebug() << "Touch point id:" << touchPoint.id() << "x:" << pos.x() << "y:" << pos.y();
                qDebug() << "Medium button";
                Game::moleAppearanceDuration=1500;
                EasyButtonTouchableGraphicsItem::hide();
                HardButtonTouchableGraphicsItem::hide();
                Scene::selfptr->hideGameOver();
                Scene::selfptr->startGame();
            }
        }
    }
//        if(event->type()==QEvent::TouchBegin){
//            qDebug() << "some touch event";
//            return true;
//        }
    return QGraphicsPixmapItem::sceneEvent(event);
};