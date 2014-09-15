#ifndef DRAGPROJECTILE_H
#define DRAGPROJECTILE_H

#include "simpleprojectile.h"

class DragProjectile : public SimpleProjectile
{
    Q_OBJECT
public:
    explicit DragProjectile(QObject *parent = 0);

    Q_INVOKABLE void initialize(double x0, double y0, double z0,
                                double vx0, double vy0, double vz0, double time,
                                double mass, double area, double density, double Cd);

    Q_INVOKABLE double getMass() const { return mass; }
    Q_INVOKABLE double getArea() const { return area; }
    Q_INVOKABLE double getDensity() const { return density; }
    Q_INVOKABLE double getCd() const { return Cd; }

    Q_INVOKABLE virtual void updateLocationAndVelocity(double dt);
    Q_INVOKABLE virtual double *getRightHandSide(double s, double q[], double deltaQ[],
                             double ds, double qScale) override;
    Q_INVOKABLE void setArea(double area);
    Q_INVOKABLE void setCd(double Cd);
protected:
    double getDensityForAltitude(double altitude);

private:
    double mass;
    double area;
    double density;
    double Cd;


signals:


public slots:

};

#endif // DRAGPROJECTILE_H
