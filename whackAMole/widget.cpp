#include "widget.h"
#include "ui_widget.h"
# include <QDebug>
#include <QScrollBar>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
;

    ui->graphicsView->setStyleSheet("QScrollBar:horizontal {height: 0;}");
    ui->graphicsView->setStyleSheet("QScrollBar:vertical {width: 0;}");
    //this->setStyleSheet("QScrollBar:vertical {width: 0;}");
    this->setStyleSheet("QScrollBar:horizontal {height: 0;}");


    this->setAttribute(Qt::WA_AcceptTouchEvents, true);

    Scene *scene = new Scene();

    scene -> setSceneRect(0,0,480,272);
    Scene::selfptr = scene;
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/bg.png"));
    scene->addItem(pixItem); // adds mole_bg

    ui-> graphicsView ->setScene(scene); // game screen
    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents); //make it accept touch events

    //connect(ui->startButton, &QPushButton::clicked, this, &Widget::on_startButton_clicked);


}


Widget::~Widget()
{
    delete ui;
}


