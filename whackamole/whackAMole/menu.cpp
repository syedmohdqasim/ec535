#include "menu.h"

menu::menu(QObject *parent)
    : QObject{parent}
{

    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/bg.png"));
    scene->addItem(pixItem); // adds mole_bg


}
