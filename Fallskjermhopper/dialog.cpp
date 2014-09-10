#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setFocus();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(-395, -465, 790, 930);

    QPixmap background(":/Images/fallskjermhopper_bg.png");
    backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(-395, -465);
    scene->addItem(backgroundItem);

    QPixmap playerIcon(":/Images/fallskjermhopper_player_nopara.png");
    skydiver = new Skydiver(0.0, 4000, 50, 0.4, playerIcon );
    scene->addItem(skydiver);

    keyDown = false;
    swingTimer = new QTimer(this);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));

    timer->start(30);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        skydiver->setSwingForce(1000);
    }

    if(event->key() == Qt::Key_A)
    {
        skydiver->setSwingForce(-1000);
    }

    if(event->key() == Qt::Key_Space) skydiver->releaseParachute();

}

void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        skydiver->setSwingForce(0);
    }

    if(event->key() == Qt::Key_A)
    {
        skydiver->setSwingForce(0);
    }
}
