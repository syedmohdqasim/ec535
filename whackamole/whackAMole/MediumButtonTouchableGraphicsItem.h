//
// Created by sqasim on 4/23/23.
//
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