#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QTimerEvent>
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
    void resetGame();
    void setTime();
    void endGame();

signals:
    void timeChanged(int);

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *timeTaker;

    QGraphicsPixmapItem *backgroundItem;
    Skydiver *skydiver;
    QGraphicsEllipseItem *landingPlatform;

    int maxLandingVelocity;
    int wind;
    int time;
    bool gameFinished;


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);
    void timerEvent(QTimerEvent *);

};

#endif // DIALOG_H
