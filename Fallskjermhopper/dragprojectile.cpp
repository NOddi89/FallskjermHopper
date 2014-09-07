#include "dragprojectile.h"
#include "odesolver.h"
#include <QDebug>
#include <QtMath>

DragProjectile::DragProjectile(QObject *parent) :
    SimpleProjectile(parent)
{
    this->mass = 0.0;
    this->area = 0.0;
    this->density = 0.0;
    this->Cd = 0.0;
}

void DragProjectile::initialize(double x0, double y0, double z0, double vx0, double vy0, double vz0, double time, double mass, double area, double density, double Cd)
{
    SimpleProjectile::initialize(x0, y0, z0, vx0, vy0, vz0, time);

    this->mass = mass;
    this->area = area;
    this->density = density;
    this->Cd = Cd;
}

void DragProjectile::updateLocationAndVelocity(double dt)
{
    ODESolver::rungeKutta4(this, dt);
}

double *DragProjectile::getRightHandSide(double s, double q[], double deltaQ[],
                                         double ds, double qScale)
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

    // compute the velocity magnitude. Add a small amount
    // (1.0e-8) to avoid div-by-zero errors if all velocity
    // components are zero
    double v = qSqrt(vx * vx + vy * vy + vz * vz) + 1.0e-8;


    // compute total drag force
    double Fd = 0.5 * getDensityForAltitude(getZ()) * area * Cd * v * v;

    // compute the right hand side of the six ODEs
    dQ[0] = -ds * Fd * vx/(mass * v);
    dQ[1] = ds * vx;
    dQ[2] = -ds * Fd * vy/(mass * v);
    dQ[3] = ds * vy;
    dQ[4] = ds * (G - Fd * vz/(mass * v));
    dQ[5] = ds * vz;

    return dQ;
}

double DragProjectile::getDensityForAltitude(double altitude)
{
    // used regression to find a formula for density for a given altitude
    // when density at sea-level is 1.225.
    // Range of input to regression: 0 to 3048m

    double res = 4.226958907191e-09 * (altitude * altitude) - 1.1786444511242e-04 * altitude + 1.2248168626609;
    qDebug() << "density: " << res;
    return res;
}

