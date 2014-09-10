#include "skydiver.h"
#include <QPainter>
#include <QDebug>

Skydiver::Skydiver(double xPos, double altitude, double mass, double area, QPixmap icon)
{   
    flyTime = 0;

    //skydiverODE = new WindProjectile();
    skydiverODE = new SkydiverODE();
    skydiverODE->initialize(xPos, 0.0, altitude,        //x0, y0, z0
                            0.0, 0.0, 0.0,             //vx0, vy0, vz0
                            flyTime, mass, area,        //time, mass, area
                            1.225, 0.44, 0.0, 0.0 );    //density, cd, wind x, wind y

    this->setPixmap(QPixmap(":/Images/fallskjermhopper_player_nopara.png"));
    this->setScale(0.5);

}

QRectF Skydiver::boundingRect() const
{
    return QRectF(0,0, pixmap().width(), pixmap().height());
}

void Skydiver::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->drawPixmap(rect, pixmap(), rect);
}

void Skydiver::setSwingForce(double value)
{
    skydiverODE->setSwingForce(value);
}

void Skydiver::releaseParachute()
{
    setPixmap(QPixmap(":/Images/fallskjermhopper_player.png"));
    setScale(0.05);
    skydiverODE->setArea(20);
    skydiverODE->setCd(1.4);
}

//void Skydiver::setSwingVx(double value)
//{
//    skydiverODE->setSwingVx(value);
//}

void Skydiver::advance(int phase)
{
    if(!phase) return;
    flyTime += 0.03;
    skydiverODE->updateLocationAndVelocity(0.03);

    setPos(0+(skydiverODE->getX()), -465-(skydiverODE->getZ()-4000) );
}
