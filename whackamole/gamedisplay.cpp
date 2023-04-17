#include "gamedisplay.h"
#include "ui_gamedisplay.h"

gamedisplay::gamedisplay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamedisplay)
{
    ui->setupUi(this);
}

gamedisplay::~gamedisplay()
{
    delete ui;
}



