//
// Created by sqasim on 4/23/23.
//

#ifndef MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H
#define MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>


class MediumButtonTouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    static MediumButtonTouchableGraphicsItem * selfptr;
    static void hide();
    explicit MediumButtonTouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
    selfptr=this;
};

protected:
    bool sceneEvent(QEvent* event) override;

};

#endif //MEDIUMBUTTONTOUCHABLEGRAPHICSITEM_H