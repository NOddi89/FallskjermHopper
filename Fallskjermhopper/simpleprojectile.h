#ifndef SIMPLEPROJECTILE_H
#define SIMPLEPROJECTILE_H

#include "ode.h"

class SimpleProjectile : public ODE
{
    Q_OBJECT
public:
    // Gravitational acceleration. Initialized in .cpp
    static const double G;

    SimpleProjectile( QObject *parent = 0);

    Q_INVOKABLE virtual void initialize(
            double x0, double y0, double z0,
            double vx0, double vy0, double vz0,
            double time);

    // simple property getters
    Q_INVOKABLE double getVx() { return getQ(0); }
    Q_INVOKABLE double getVy() { return getQ(2); }
    Q_INVOKABLE double getVz() { return getQ(4); }
    Q_INVOKABLE double getX() { return getQ(1); }
    Q_INVOKABLE double getY() { return getQ(3); }
    Q_INVOKABLE double getZ() { return getQ(5); }
    Q_INVOKABLE double getTime() { return getS(); }

    Q_INVOKABLE double getVelocity();
    Q_INVOKABLE void updateLocationAndVelocity(double dt);
    Q_INVOKABLE virtual double *getRightHandSide(
            double s, double q[], double deltaQ[],
            double ds, double qScale) override;

};

#endif // SIMPLEPROJECTILE_H
