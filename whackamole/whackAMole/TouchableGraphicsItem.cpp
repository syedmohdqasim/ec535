//
// Created by sqasim on 4/23/23.
//
#include "TouchableGraphicsItem.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QEvent>

bool TouchableGraphicsItem::sceneEvent(QEvent* event)  {
        qDebug() << "some event";
        if(event->type()==QEvent::TouchBegin){
            qDebug() << "some touch event";
            return true;
        }
    return QGraphicsPixmapItem::sceneEvent(event);
};