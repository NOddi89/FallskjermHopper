#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    //scene setup
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setFocus();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(-395, -465, 790, 930);

    //UI Connections
    connect(ui->slider_radius, SIGNAL(valueChanged(int)),
            ui->label_radiusSliderValue, SLOT(setNum(int)));
    connect(ui->slider_weigth, SIGNAL(valueChanged(int)),
            ui->label_weigthSliderValue, SLOT(setNum(int)));
    connect(ui->slider_velocity, SIGNAL(valueChanged(int)),
            ui->label_velocitySliderValue, SLOT(setNum(int)));
    connect(ui->pushButton_start, SIGNAL(clicked()),
            this, SLOT(startGame()));

    //Images
    QPixmap background(":/Images/fallskjermhopper_bg.png");
    backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(-395, -465);
    scene->addItem(backgroundItem);

//    QPixmap playerIcon(":/Images/fallskjermhopper_player_nopara.png");
//    skydiver = new Skydiver(0.0, 4000, 50, 0.4, playerIcon );
//    scene->addItem(skydiver);


    //Timers
    swingTimer = new QTimer(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));

//    timer->start(30);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startGame()
{
    if(!timer->isActive())
    {
        QPixmap playerIcon(":/Images/fallskjermhopper_player_nopara.png");
        skydiver = new Skydiver(0.0, 4000, ui->slider_weigth->value(), (3.14*qPow((ui->slider_radius->value())/100.0, 2)), playerIcon );
        scene->addItem(skydiver);

        maxLandingVelocity = ui->slider_velocity->value();

        timer->start(30);

        //double radius = ui->slider_radius->value()/100.0;
        qDebug() << 3.14*qPow((ui->slider_radius->value())/100.0, 2);
    }
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
