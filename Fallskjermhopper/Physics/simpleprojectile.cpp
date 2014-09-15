#include "simpleprojectile.h"
#include <QDebug>
#include <QtMath>
const double SimpleProjectile::G = -9.81;

SimpleProjectile::SimpleProjectile(QObject *parent)
    :ODE(6)
{
    Q_UNUSED(parent)

    // store default values to s and q array of the ODE class
    setS(0);
    setQ(0, 0);
    setQ(0, 1);
    setQ(0, 2);
    setQ(0, 3);
    setQ(0, 4);
    setQ(0, 5);
}

void SimpleProjectile::initialize(
        double x0, double y0, double z0,
        double vx0, double vy0, double vz0,
        double time)
{
    // store parameters to s and q array of the ODE class
    setS(time);
    setQ(vx0, 0);
    setQ(x0, 1);
    setQ(vy0, 2);
    setQ(y0, 3);
    setQ(vz0, 4);
    setQ(z0, 5);
}

double SimpleProjectile::getVelocity()
{
    //return sqrt(getQ(0) * getQ(0) + getQ(2) * getQ(2) + getQ(4) * getQ(4));
    return qSqrt(getQ(0) * getQ(0) + getQ(2) * getQ(2) + getQ(4) * getQ(4));
}

void SimpleProjectile::updateLocationAndVelocity(double dt)
{
    // retrieve values stored in ODE class
    double time = getS();
    double vx0 = getQ(0);
    double vy0 = getQ(2);
    double vz0 = getQ(4);
    double x0 = getQ(1);
    double y0 = getQ(3);
    double z0 = getQ(5);

    // Update xyz locations and the z-component of velocity.
    // No change in x- and y-velocities
    double x = x0 + vx0 * dt;
    double y = y0 + vy0 * dt;
    double z = z0 + vz0 * dt + 0.5 * G * dt * dt;

    double vz = vz0 + G * dt;

    // update time
    time = time + dt;

    // store values to ODE class
    setS(time);
    setQ(x, 1);
    setQ(y, 3);
    setQ(z, 5);
    setQ(vz, 4);

}

// getRightHandSide() is abstract in ODE. SimpleProjectile does not solve
// any ODEs, so we return a dummy array...
double *SimpleProjectile::getRightHandSide(double s, double q[], double deltaQ[], double ds, double qScale)
{
    Q_UNUSED(s)
    Q_UNUSED(qScale)
    Q_UNUSED(ds)
    Q_UNUSED(deltaQ)
    Q_UNUSED(q)
    return new double[1];
}


