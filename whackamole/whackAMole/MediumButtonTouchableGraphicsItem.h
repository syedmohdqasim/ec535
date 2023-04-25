//
// Created by sqasim on 4/23/23.
//

#ifndef MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H
#define MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H
#endif //MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>


class MediumButtonTouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    explicit MediumButtonTouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
};
protected:
    bool sceneEvent(QEvent* event) override;
};