#include "windprojectile.h"
#include "odesolver.h"
#include <QDebug>
#include <QtMath>

WindProjectile::WindProjectile(QObject *parent) : DragProjectile(parent)
{
    this->windVx = 0.0;
    this->windVy = 0.0;
}

void WindProjectile::initialize(double x0, double y0, double z0, double vx0, double vy0, double vz0, double time, double mass, double area, double density, double Cd, double windVx, double windVy)
{
    DragProjectile::initialize(x0, y0, z0, vx0, vy0, vz0, time, mass, area, density, Cd);

    this->windVx = windVx;
    this->windVy = windVy;
}

// The getRightHandSide() method returns the right-hand sides of the six first-order
// projectile ODEs.
// q[0] = vx = dxdt
// q[1] = x
// q[2] = vy = dydt
// q[3] = y
// q[4] = vz = dzdt
// q[5] = z
double *WindProjectile::getRightHandSide(double s, double q[], double deltaQ[], double ds, double qScale)
{
    Q_UNUSED(s);
    double *dQ = new double[6];
    double *newQ = new double[6];

    // compute the intermediate values of the dependent variables
    for (int i = 0; i < 6; ++i) {
        newQ[i] = q[i] + qScale * deltaQ[i];
    }

    double vx = newQ[0];
    double vy = newQ[2];
    double vz = newQ[4];

    // Compute the apparent velocities by subtracting the wind velocity
    // components from the projectile velocity components
    double vax = vx - windVx;
    double vay = vy - windVy;
    double vaz = vz;

    // compute the velocity magnitude. Add a small amount
    // (1.0e-8) to avoid div-by-zero errors if all velocity
    // components are zero
    double va = qSqrt(vax * vax + vay * vay + vaz * vaz) + 1.0e-8;


    // compute total drag force
    double Fd = 0.5 * getDensityForAltitude(getZ()) * getArea() * getCd() * va * va;

    // compute the right hand side of the six ODEs
    dQ[0] = -ds * Fd * vax/(getMass() * va);
    dQ[1] = ds * vx;
    dQ[2] = -ds * Fd * vay/(getMass() * va);
    dQ[3] = ds * vy;
    dQ[4] = ds * (G - Fd * vaz/(getMass() * va));
    dQ[5] = ds * vz;

    return dQ;
}
double WindProjectile::getWindVx() const
{
    return windVx;
}

void WindProjectile::setWindVx(double value)
{
    windVx = value;
}
double WindProjectile::getWindVy() const
{
    return windVy;
}

void WindProjectile::setWindVy(double value)
{
    windVy = value;
}


