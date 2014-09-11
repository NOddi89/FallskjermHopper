#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QtMath>

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

private slots:
    void startGame();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *swingTimer;

    QGraphicsPixmapItem *backgroundItem;
    Skydiver *skydiver;

    int maxLandingVelocity;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);

};

#endif // DIALOG_H
