//
// Created by sqasim on 4/23/23.
//
#ifndef EASYBUTTONTOUCHABLEGRAPHICSITEM_H
#define EASYBUTTONTOUCHABLEGRAPHICSITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>



class EasyButtonTouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    static EasyButtonTouchableGraphicsItem * selfptr;
    static void hide();

    explicit EasyButtonTouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
    selfptr=this;
};

protected:
    bool sceneEvent(QEvent* event) override;

};

#endif //EASYBUTTONTOUCHABLEGRAPHICSITEM_H