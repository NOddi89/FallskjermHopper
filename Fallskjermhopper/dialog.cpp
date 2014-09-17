#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QTime>

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
    connect(ui->pushButton_reset, SIGNAL(clicked()),
            this, SLOT(resetGame()));
    connect(this, SIGNAL(timeChanged(int)),
            ui->lcdNumber, SLOT(display(int)));



    //Images
    QPixmap background(":/Images/fallskjermhopper_bg.png");
    backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(-395, -465);
    scene->addItem(backgroundItem);

    // Other
    gameFinished = false;


    //Timers
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timeTaker = new QTimer(this);
    time = 0;
    connect(timeTaker, SIGNAL(timeout()), this, SLOT(setTime()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(setUiTimer()));

//    timer->start(30);


}

void Dialog::displayEndGameMessage(QString s)
{
    endgameMessage = new QGraphicsTextItem(s);
    endgameMessage->setFont(QFont("Times", 20, QFont::Bold));
    QFontMetrics fm(endgameMessage->font());
    int stringWidth = fm.width(endgameMessage->toPlainText());
    int messageXPos = (backgroundItem->boundingRect().width() - stringWidth)/2;
    endgameMessage->setPos(-395 + messageXPos, 0);
    scene->addItem(endgameMessage);
}

void Dialog::timerEvent(QTimerEvent *)
{
    qDebug() << "Timer event";
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startGame()
{
    if(!timer->isActive() && !gameFinished)
    {
        QPixmap playerIcon(":/Images/fallskjermhopper_player_nopara.png");
        skydiver = new Skydiver(0, 4000, ui->slider_weigth->value(), (3.14*qPow((ui->slider_radius->value())/100.0, 2)), playerIcon );
        skydiver->setZValue(1);
        scene->addItem(skydiver);

        //Connections to skydiverODE
        connect(skydiver->getSkydiverODE(), SIGNAL(zPosChanged(int)),
                ui->label_stats_altitude, SLOT(setNum(int)));
        connect(skydiver->getSkydiverODE(), SIGNAL(vzChanged(int)),
                ui->label_stats_speed, SLOT(setNum(int)));
        connect(skydiver->getSkydiverODE(), SIGNAL(atGround()),
                this, SLOT(endGame()));


        maxLandingVelocity = ui->slider_velocity->value();

        // Randow wind strength and direction
        qsrand(QTime::currentTime().second());

        wind = (qrand() % 5) + 1;
        int temp = qrand();
        if(temp % 2) wind = wind * -1;
        skydiver->setWindVx((double)wind);
        ui->label_stats_windValue->setText(QString::number(wind));

        if(wind < 0) ui->label_stats_windDirection->setText("<---");
        else ui->label_stats_windDirection->setText("--->");

        //Area
        double area = 3.14*qPow((ui->slider_radius->value())/100.0, 2);
        skydiver->setArea(area);

        //Create a landing platform

        // random x pos:
        if(temp % 2)platformXPos = 1 + qrand() % 295;
        else platformXPos = (1 + qrand() % 395)*-1;

        platformYPos = 340;
        landingPlatform = new QGraphicsEllipseItem(platformXPos, platformYPos, 100, 40);
        landingPlatform->setBrush(QBrush(Qt::red));
        scene->addItem(landingPlatform);

        // Start time taker
        timeTaker->start(1000);

        // Start game timer
        timer->start(30);

    }
}

void Dialog::resetGame()
{
    if( timer->isActive() || gameFinished )
    {
        timer->stop();
        timeTaker->stop();
        time = 0;
        delete skydiver;
        delete landingPlatform;
        delete endgameMessage;


        ui->label_stats_altitude->setNum(0);
        ui->label_stats_speed->setNum(0);
        ui->label_stats_windValue->setNum(0);
        ui->label_stats_windDirection->setText("");
        ui->lcdNumber->display(0);

        gameFinished = false;

    }
}

void Dialog::setTime()
{
    time+=1;
    emit timeChanged(time);
}

//= BUG =
//Blir kalt opp flere ganger når han er på bakken
void Dialog::endGame()
{
    gameFinished = true;
    timer->stop();
    timeTaker->stop();

    //check if we hit landing platform
    int skydiverCurrX = skydiver->x() + 45;

    if(skydiver->getSkydiverODE()->getVelocity() > maxLandingVelocity)
    {
        displayEndGameMessage(QString("You Are DEAD! To high speed!!!!"));
    }
    else if(skydiverCurrX > 395 || skydiverCurrX < -395)
    {
        displayEndGameMessage(QString("Did you fly away to Africa?"));
    }

    else if(skydiverCurrX >= platformXPos && skydiverCurrX <= platformXPos + landingPlatform->boundingRect().width())
    {
        displayEndGameMessage(QString("You landed safely. You are a true skydiver!"));
    }
    else
    {
        displayEndGameMessage(QString("Almost, but try to hit the landingplatform next time"));
    }

}


//maby add down force
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
