#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(-395, -465, 790, 930);

    // ":/Images/fallskjermhopper_bg.png"
    QPixmap background(":/Images/fallskjermhopper_bg.png");
    backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(-395, -465);
    scene->addItem(backgroundItem);

    QPixmap playerIcon(":/Images/fallskjermhopper_player_nopara.png");
    skydiver = new Skydiver(0.0, 4000, 50, 0.4, playerIcon );
    scene->addItem(skydiver);
//    skydiverStartXPos = 0.0;
//    skydiverStartAltitude = 4000;

//    skydiver = new WindProjectile();
//    skydiver->initialize(skydiverStartXPos, 0.0, skydiverStartAltitude
//                         ,40.0, 0.0, 0.0
//                         ,0.0, 50.0, 20.0, 1.225, 0.44
//                         ,5.0, 0.0);

//    skydiverImage = new QGraphicsPixmapItem(
//                QPixmap(":/Images/fallskjermhopper_player_nopara.png"));
//    skydiverImage->setPos(skydiver->getX(), skydiver->getZ());
//    skydiverImage->setScale(0.5);

//    scene->addItem(skydiverImage);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));


    timer->start(30);


}

Dialog::~Dialog()
{
    delete ui;
}
