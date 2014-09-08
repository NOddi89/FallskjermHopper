#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <skydiver.h>




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;

    QGraphicsPixmapItem *backgroundItem;
    Skydiver *skydiver;
   // WindProjectile *skydiver;

    float skydiverStartXPos;
    float skydiverStartAltitude;

};

#endif // DIALOG_H
