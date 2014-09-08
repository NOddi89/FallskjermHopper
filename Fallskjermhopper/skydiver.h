#ifndef SKYDIVER_H
#define SKYDIVER_H

#include <QGraphicsPixmapItem>
#include "Physics/windprojectile.h"

class Skydiver : public QGraphicsPixmapItem
{
public:
    Skydiver(double xPos, double altitude, double mass, double area, QPixmap icon);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    QPixmap icon;
    WindProjectile *skydiverODE;

    double flyTime;
};

#endif // SKYDIVER_H
