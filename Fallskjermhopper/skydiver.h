#ifndef SKYDIVER_H
#define SKYDIVER_H

#include <QGraphicsPixmapItem>
#include "Physics/windprojectile.h"
#include "skydiverode.h"

class Skydiver : public QGraphicsPixmapItem
{
public:
    Skydiver(double xPos, double altitude, double mass, double area, QPixmap icon);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSwingForce(double value);
    void releaseParachute();
    void setArea(double a);
    void setWindVx(double value);
    void setFlyTime(double value);

    SkydiverODE *getSkydiverODE() const;

    bool isParachuteReleased();

    double getFlyTime() const;

    ~Skydiver();

protected:
    void advance(int phase);

private:
    QPixmap icon;
    SkydiverODE *skydiverODE;

    double flyTime;
    bool parachuteReleased;
};

#endif // SKYDIVER_H
