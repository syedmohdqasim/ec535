#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gamedisplay; }
QT_END_NAMESPACE

class gamedisplay : public QMainWindow
{
    Q_OBJECT

public:
    gamedisplay(QWidget *parent = nullptr);
    ~gamedisplay();

private:
    Ui::gamedisplay *ui;
};
#endif // GAMEDISPLAY_H
