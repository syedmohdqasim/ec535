//
// Created by sqasim on 4/23/23.
//
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