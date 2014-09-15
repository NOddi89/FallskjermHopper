#ifndef WINDPROJECTILE_H
#define WINDPROJECTILE_H

#include "dragprojectile.h"

class WindProjectile : public DragProjectile
{
    Q_OBJECT
public:
    WindProjectile(QObject *parent = 0);

    Q_INVOKABLE void initialize(double x0, double y0, double z0,
                                double vx0, double vy0, double vz0, double time,
                                double mass, double area, double density, double Cd,
                                double windVx, double windVy);

    Q_INVOKABLE virtual double *getRightHandSide(double s, double q[], double deltaQ[],
                             double ds, double qScale) override;
    double getWindVx() const;
    void setWindVx(double value);

    double getWindVy() const;
    void setWindVy(double value);

signals:

private:
    double windVx;
    double windVy;
};

#endif // WINDPROJECTILE_H
