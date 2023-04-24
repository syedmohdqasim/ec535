#include "widget.h"
#include "ui_widget.h"
# include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
;


    this->setStyleSheet("QScrollBar:vertical {width: 0;}");
    this->setStyleSheet("QScrollBar:horizontal {height: 0;}");
    ui->graphicsView->setStyleSheet("QScrollBar:horizontal {height: 0;}");
    ui->graphicsView->setStyleSheet("QScrollBar:vertical {width: 0;}");

    this->setAttribute(Qt::WA_AcceptTouchEvents, true);
    Scene *scene = new Scene();
    scene -> setSceneRect(0,0,480,272);

    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/bg.png"));
    scene->addItem(pixItem); // adds mole_bg
    //qDebug() << pixItem->zValue;
    //pixItem->setPos() // for repositioning BG
    // pixItem->setAcceptTouchEvents(true);


    ui-> graphicsView ->setScene(scene); // game screen
//    ui->graphicsView->setAcceptTouchEvents(true);
    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

}


Widget::~Widget()
{
    delete ui;
}



void Widget::on_startButton_clicked()
{
    qDebug() << "game started";
    scene->startGame();
}
