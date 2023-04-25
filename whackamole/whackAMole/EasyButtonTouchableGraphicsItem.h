//
// Created by sqasim on 4/23/23.
//
#ifndef EASYBUTTONTOUCHABLEGRAPHICSITEM_H
#define EASYBUTTONTOUCHABLEGRAPHICSITEM_H
#endif //EASYBUTTONTOUCHABLEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>



class EasyButtonTouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    explicit EasyButtonTouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
};
protected:
    bool sceneEvent(QEvent* event) override;
};