#include "skydiver.h"
#include <QPainter>
#include <QDebug>

// = BUG =
//Få skydiver til å kunne sende signals, qobject problem...
// Da kan man heller sjekke z pos for å ende gamet i advance metoden
// i stedenfor i getrighthandside på skydiverode
Skydiver::Skydiver(double xPos, double altitude, double mass, double area, QPixmap icon)
{   
    flyTime = 0;
    parachuteReleased = false;

    //skydiverODE = new WindProjectile();
    skydiverODE = new SkydiverODE();
    skydiverODE->initialize(xPos, 0.0, altitude,        //x0, y0, z0
                            0.0, 0.0, 0.0,             //vx0, vy0, vz0
                            flyTime, mass, area,        //time, mass, area
                            1.225, 0.44, 0.0, 0.0 );    //density, cd, wind x, wind y

    this->setPixmap(QPixmap(":/Images/fallskjermhopper_nopara.png"));
    this->setScale(0.3);


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
    setPixmap(QPixmap(":/Images/fallskjermhopper_player2.png"));
    setScale(0.3);
    skydiverODE->setArea(20);
    skydiverODE->setCd(1.4);
    parachuteReleased = true;

}

bool Skydiver::isParachuteReleased()
{
    return parachuteReleased;
}

void Skydiver::setArea(double a)
{
    skydiverODE->setArea(a);
}

void Skydiver::setWindVx(double value)
{
    skydiverODE->setWindVx(value);
}

Skydiver::~Skydiver()
{
    delete skydiverODE;
}

//void Skydiver::setSwingVx(double value)
//{
//    skydiverODE->setSwingVx(value);
//}

void Skydiver::advance(int phase)
{
    if(!phase) return;

    if(skydiverODE->getZ() <= 0)skydiverODE->emitAtGround();

    flyTime += 0.03;
    skydiverODE->updateLocationAndVelocity(0.03);


    double zScale = (800.0 / 4000.0);
    double xScale = (0.5);
    // 465
    //qDebug() << boundingRect().height();
    setPos(0+(skydiverODE->getX())*xScale, -565-(skydiverODE->getZ()-4000)*zScale );

}
double Skydiver::getFlyTime() const
{
    return flyTime;
}

void Skydiver::setFlyTime(double value)
{
    flyTime = value;
}

SkydiverODE *Skydiver::getSkydiverODE() const
{
    return skydiverODE;
}


