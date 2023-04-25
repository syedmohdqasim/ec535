#ifndef MENU_H
#define MENU_H

#include <QObject>

class menu : public QObject
{
    Q_OBJECT
public:
    explicit menu(QObject *parent = nullptr);

signals:

};

#endif // MENU_H
