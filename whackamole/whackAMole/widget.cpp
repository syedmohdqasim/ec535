#include "widget.h"
#include "ui_widget.h"
#include "TouchableGraphicsItem.h"
# include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
;

    this->setAttribute(Qt::WA_AcceptTouchEvents, true);
    Scene *scene = new Scene();
    scene -> setSceneRect(0,0,480,272);

    QGraphicsPixmapItem *pixItem = new TouchableGraphicsItem(QPixmap(":/images/bg.png"));
    scene->addItem(pixItem); // adds mole_bg
    //qDebug() << pixItem->zValue;
    //pixItem->setPos() // for repositioning BG
    pixItem->setAcceptTouchEvents(true);


    ui -> pointsDisp ->setStyleSheet("color: red;"); //point text
    ui-> graphicsView ->setScene(scene); // game screen
//    ui->graphicsView->setAcceptTouchEvents(true);
    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

}


Widget::~Widget()
{
    delete ui;
}
