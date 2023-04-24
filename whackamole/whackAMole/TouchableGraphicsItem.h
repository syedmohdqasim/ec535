//
// Created by sqasim on 4/23/23.
//
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

class TouchableGraphicsItem : public QGraphicsPixmapItem {
public:
    explicit TouchableGraphicsItem(const QPixmap& pixmap):QGraphicsPixmapItem(pixmap){
    setAcceptTouchEvents(true);
};
protected:
    bool sceneEvent(QEvent* event) override;
};