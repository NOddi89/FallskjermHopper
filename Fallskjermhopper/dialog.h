#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QtMath>

#include "skydiver.h"




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void displayEndGameMessage(QString s);


    ~Dialog();

private slots:
    void startGame();
    void resetGame();
    void setTime();
    void endGame();
    void testSlot();

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
    QGraphicsTextItem *endgameMessage;

    int maxLandingVelocity;
    int wind;
    int time;
    bool gameFinished;
    int platformXPos;
    int platformYPos;


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);
    void timerEvent(QTimerEvent *);

};

#endif // DIALOG_H
