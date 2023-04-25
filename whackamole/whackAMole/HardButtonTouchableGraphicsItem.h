//
// Created by sqasim on 4/23/23.
//

#ifndef HARDBUTTONTOUCHABLEGRAPHICSITEM_H
#define HARDBUTTONTOUCHABLEGRAPHICSITEM_H



#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>



class HardButtonTouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    static HardButtonTouchableGraphicsItem * selfptr;
    static void hide();
    explicit HardButtonTouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
        selfptr=this;
};

protected:
    bool sceneEvent(QEvent* event) override;

};

#endif //HARDBUTTONTOUCHABLEGRAPHICSITEM_H